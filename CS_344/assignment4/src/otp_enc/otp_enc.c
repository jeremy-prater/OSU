#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include "common.h"

static int clientPort = -1;
static int clientSocket = -1;
static int clientConnection = -1;

int main(int argc, char *argv[])
{
	int socketFD, portNumber, charsWritten, charsRead;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char plainTextFile[1024];
    char keyFile[1024];
    
    if (argc != 4)
    {
        fprintf (stderr, "%s [plain text file] [key file] [server port]\n", argv[0]);
        return -1;
    }

    if (sscanf (argv[1], "%s", plainTextFile) != 1)
    {
        fprintf (stderr, "Invalid text file [%s]", argv[1]);
        return -1;       
    }
    if (sscanf (argv[2], "%s", keyFile) != 1)
    {
        fprintf (stderr, "Invalid key file [%s]", argv[1]);
        return -2;
    }
    if ((sscanf (argv[3], "%d", &clientPort) != 1) || (clientPort < 0) || (clientPort > 0xFFFF))
    {
        fprintf (stderr, "Invalid port!! Must be 0-65535 [%d]\n\n", clientPort);
        return -3;       
    }

    // Create TCP socket on port
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf (stderr, "Failed to create TCP client socket [%s]\n\n", strerror(errno));
        return -errno;
    }

    struct sockaddr_in ftClientSock;
    memset (&ftClientSock, 0, sizeof (ftClientSock));
    ftClientSock.sin_family = AF_INET;
    ftClientSock.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    ftClientSock.sin_port = htons(clientPort);

	// Connect to server
	if (connect(clientSocket, (struct sockaddr*)&ftClientSock, sizeof(ftClientSock)) < 0)
    {
        fprintf (stderr, "Failed to connect to service [%s]\n", strerror(errno));
        return -errno;
    }


    // Fork off here with new connection...
    uint32_t clientMagic = OTP_ENC_MAGIC;
    send(clientSocket, &clientMagic, sizeof (clientMagic), 0);
    uint32_t serverMagic = 0;
    recv(clientSocket, &serverMagic, sizeof (serverMagic), 0);
    fprintf(stderr, "Server authenticated [0x%08x]\n", serverMagic);
    fflush(stderr);

	close(clientSocket); // Close the socket
	return 0;
}
