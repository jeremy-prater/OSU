#include "ftserver.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include "ftserver-data.h"

static int serverPort = -1;
static int serverSocket = -1;
static int serverConnection = -1;

static uint8_t controlData[4096];

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        printf("Invald arguments!\n\n%s <server port>\n", argv[0]);
        return -1;
    }

    if ((sscanf (argv[1], "%d", &serverPort) != 1) || (serverPort < 0) || (serverPort > 0xFFFF))
    {
        printf("Invalid port!! Must be 0-65535 [%d]\n\n", serverPort);
        return -1;       
    }

    // Create TCP socket on port
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("Failed to create TCP server socket [%s]\n\n", strerror(errno));
        return -errno;
    }

    struct sockaddr_in ftServerSock;
    memset (&ftServerSock, 0, sizeof (ftServerSock));
    ftServerSock.sin_family = AF_INET;
    ftServerSock.sin_addr.s_addr = htonl(INADDR_ANY);
    ftServerSock.sin_port = htons(serverPort);

    // Bind to port
    if (bind(serverSocket, (struct sockaddr*)&ftServerSock, sizeof (ftServerSock)) < 0)
    {
        printf("Failed to bind TCP server socket [%s]\n\n", strerror(errno));
        return -errno;
    }

    if (listen(serverSocket, 5) < 0)
    {
        printf("Failed to listen on TCP server socket [%s]\n\n", strerror(errno));
        return -errno;
    }

    socklen_t ftServerSocketLen = sizeof (ftServerSock);
    while ((serverConnection = accept (serverSocket, (struct sockaddr*)&ftServerSock, &ftServerSocketLen)) >= 0)
    {
        if (serverConnection < 0)
        {
            printf ("Connection Failed! [%s]\n", strerror(errno));
        }
        else
        {
            printf ("New Connection! [%d]\n", serverConnection);

            // Receive command/header
            printf ("Waiting for header...\n");
            fflush(stdout);
            memset (controlData, 0, sizeof (controlData));
            ssize_t recvSize = recv(serverConnection, controlData, sizeof (controlData), 0);

            ftserverCommandHeader * header = (ftserverCommandHeader *)controlData;
            header->dataPort = ntohs(header->dataPort);
            header->payloadLength = ntohs(header->payloadLength);
            header->hostnameLength = ntohs(header->hostnameLength);
            char * hostname = (char*)malloc (header->hostnameLength + 1);
            memset (hostname, 0, header->hostnameLength + 1);
            memcpy (hostname, header->payload, header->hostnameLength);
            uint8_t * payload = header->payload + header->hostnameLength;

            printf ("Header recv\nData port : %d\nCommand: %d\npayloadLength: %d\nhost: %s\n",
                header->dataPort,
                header->command,
                header->payloadLength,
                hostname);

            if (header->payloadLength > 0)
            {
                printf ("Payload: %s\n", payload);
            }

            // Create listener socket on dataPort
            uint8_t * serverResponse = GetServerResponse(hostname, header->dataPort, header->command, payload);

            free (hostname);
            shutdown(serverConnection, 2);
        }
    }

    printf ("Exited!!\n");
}