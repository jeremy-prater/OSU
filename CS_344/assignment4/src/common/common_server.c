#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "common.h"

static int serverPort = -1;
static int serverSocket = -1;

void HandleServerConnection(int serverConnection, uint32_t serverMagic, uint32_t clientMagicTest)
{
    // Get magic from client
    uint32_t clientMagic = 0;
    recv(serverConnection, &clientMagic, sizeof (clientMagic), 0);
    fprintf (stderr, "Client Connected, recv magic [0x%08x]\n", clientMagic);
    if (clientMagic != clientMagicTest)
    {
        printf ("Client connect with incorrect magic [0x%08x]\n", clientMagic);
    }
    else
    {
        fprintf (stderr, "Client connected, sending reply magic [0x%08x]\n", clientMagic);
        send(serverConnection, &serverMagic, sizeof (serverMagic), 0);

        // Split here for enc/dec
        uint32_t keyDataSize = 0;
        recv (serverConnection, &keyDataSize, sizeof(keyDataSize), 0);
        fprintf (stderr, "Client sent key/data size of [%u]\n", keyDataSize);

        uint8_t * keyData = GetDataRecvLoop(serverConnection, keyDataSize);
        uint8_t * fileData = GetDataRecvLoop(serverConnection, keyDataSize);

        // Do something with the key/data...
        fprintf (stderr, "Preforming encryption protocols...\n");

        uint8_t * resultData = PreformOTP(keyData, fileData, keyDataSize);

        uint32_t offset = 0;
        while (keyDataSize > 0)
        {
            uint32_t recvSize = keyDataSize;
            if (keyDataSize > 1000)
            {
                recvSize = 1000;
            }
            offset += send (serverConnection, &resultData[offset], recvSize, 0);
            keyDataSize -= offset;

        }
    }
    close(serverConnection);
    exit(0); // Should've used select in the parent... The easy way out...
}

void CreateServer (int argc, char * argv[], uint32_t serverMagic, uint32_t clientMagic)
{
    uint16_t serverPort = 0;
    uint32_t replyMagic = 0;

    if (argc != 2)
    {
        fprintf (stderr, "%s [Server port]\n", argv[0]);
        exit(-errno);
    }

    if ((sscanf (argv[1], "%d", &serverPort) != 1) || (serverPort < 0) || (serverPort > 0xFFFF))
    {
        fprintf (stderr, "Invalid port!! Must be 0-65535 [%d]\n\n", serverPort);
        exit(-errno);
    }

    // Create TCP socket on port
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf (stderr, "Failed to create TCP server socket [%s]\n\n", strerror(errno));
        exit(-errno);
    }

    struct sockaddr_in ftServerSock;
    memset (&ftServerSock, 0, sizeof (ftServerSock));
    ftServerSock.sin_family = AF_INET;
    ftServerSock.sin_addr.s_addr = htonl(INADDR_ANY);
    ftServerSock.sin_port = htons(serverPort);

    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
    {
        fprintf (stderr, "Failed to set TCP socket options [%s]\n\n", strerror(errno));
        exit(-errno);
    }

    // Bind to port
    if (bind(serverSocket, (struct sockaddr*)&ftServerSock, sizeof (ftServerSock)) < 0)
    {
        fprintf (stderr, "Failed to bind TCP server socket [%s]\n\n", strerror(errno));
        exit(-errno);
    }

    if (listen(serverSocket, 6) < 0)
    {
        fprintf (stderr, "Failed to listen on TCP server socket [%s]\n\n", strerror(errno));
        exit(-errno);
    }

    socklen_t ftServerSocketLen = sizeof (ftServerSock);
    int serverConnection = -1;

    while ((serverConnection = accept (serverSocket, (struct sockaddr*)&ftServerSock, &ftServerSocketLen)) >= 0)
    {
        if (serverConnection < 0)
        {
            fprintf (stderr, "Connection Failed! [%s]\n", strerror(errno));
        }
        else
        {
            // Fork off here with new connection!
            pid_t spawnPID = fork();
            switch (spawnPID)
            {
                case -1:
                {
                    fprintf(stderr, "Server fork failed. Nooooo!!!!");
                    exit (-100);
                }
                break;
                case 0:
                {
                    // This is the child
                    // This goes into a new process...
                    HandleServerConnection(serverConnection, serverMagic, clientMagic);
                }
                break;
                default:
                {
                    // This is the parent...
                    fprintf(stderr, "Child server launched [%u]\n", spawnPID);
                    close(serverConnection);
                    
                }
            }
        }
        fprintf (stderr, "Client disconnected!\n");
    }
}