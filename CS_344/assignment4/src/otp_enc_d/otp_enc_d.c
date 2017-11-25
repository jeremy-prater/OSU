#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>

static int serverPort = -1;
static int serverSocket = -1;
static int serverConnection = -1;
#include <time.h>

int main (int argc, char * argv[])
{
    uint16_t serverPort = 0;
    if (argc != 2)
    {
        fprintf (stderr, "%s [key length]\n", argv[0]);
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
    while ((serverConnection = accept (serverSocket, (struct sockaddr*)&ftServerSock, &ftServerSocketLen)) >= 0)
    {
        if (serverConnection < 0)
        {
            //printf ("Connection Failed! [%s]\n", strerror(errno));
        }
        else
        {
            // New connection!
            printf ("new connection!");
            fflush(stdout);

        }
    }

    exit(0);
}