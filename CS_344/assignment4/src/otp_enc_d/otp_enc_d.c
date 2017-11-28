#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "common.h"

static int serverPort = -1;
static int serverSocket = -1;

void HandleConnection(int serverConnection)
{
    // Get magic from client
    uint32_t clientMagic = 0;
    recv(serverConnection, &clientMagic, sizeof (clientMagic), 0);
    printf ("Client Connected, recv magic [0x%08x]\n", clientMagic);
    fflush(stdout);
    if (clientMagic != OTP_ENC_MAGIC)
    {
        printf ("Client connect with incorrect magic [0x%08x]\n", clientMagic);
    }
    else
    {
        fprintf (stderr, "Client connected, sending reply magic [0x%08x]\n", clientMagic);
        uint32_t serverMagic = OTP_ENC_MAGIC;
        send(serverConnection, &serverMagic, sizeof (serverMagic), 0);
    }

}

int main (int argc, char * argv[])
{
    uint16_t serverPort = 0;
    uint32_t replyMagic = 0;

    if (argc != 2)
    {
        fprintf (stderr, "%s [Server port]\n", argv[0]);
        return -1;
    }

    if ((sscanf (argv[1], "%d", &serverPort) != 1) || (serverPort < 0) || (serverPort > 0xFFFF))
    {
        fprintf (stderr, "Invalid port!! Must be 0-65535 [%d]\n\n", serverPort);
        return -1;
    }

    // Create TCP socket on port
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf (stderr, "Failed to create TCP server socket [%s]\n\n", strerror(errno));
        return -errno;
    }

    struct sockaddr_in ftServerSock;
    memset (&ftServerSock, 0, sizeof (ftServerSock));
    ftServerSock.sin_family = AF_INET;
    ftServerSock.sin_addr.s_addr = htonl(INADDR_ANY);
    ftServerSock.sin_port = htons(serverPort);

    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
    {
        fprintf (stderr, "Failed to set TCP socket options [%s]\n\n", strerror(errno));
        return -errno;
    }

    // Bind to port
    if (bind(serverSocket, (struct sockaddr*)&ftServerSock, sizeof (ftServerSock)) < 0)
    {
        fprintf (stderr, "Failed to bind TCP server socket [%s]\n\n", strerror(errno));
        return -errno;
    }

    if (listen(serverSocket, 5) < 0)
    {
        fprintf (stderr, "Failed to listen on TCP server socket [%s]\n\n", strerror(errno));
        return -errno;
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

            // This goes into a new process...
            HandleConnection(serverConnection);
        }
        fprintf (stderr, "Client disconnected!\n");
    }

    exit(0);
}