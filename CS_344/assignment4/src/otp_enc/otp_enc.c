#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
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
    uint32_t keyFileSize = 0;
    uint32_t plainTextFileSize = 0;

	uint8_t * plainTextFileData = 0;
    uint8_t * keyFileData = 0;

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

    // Read key file
    struct stat keyFileStat;
    if (stat(keyFile, & keyFileStat) < 0)
    {
        fprintf (stderr, "Invalid key file [%s] [%s]\n\n", keyFile, strerror(errno));
        return -4;
    }

    keyFileSize = keyFileStat.st_size;
    int keyFileFD = open(keyFile, O_RDONLY);
    if (keyFileFD < 0)
    {
        fprintf (stderr, "Unable to open key file [%s] [%s]\n\n", keyFile, strerror(errno));
        return -5;
    }

    keyFileData = (uint8_t *)malloc (keyFileSize);
    if (read(keyFileFD, keyFileData, keyFileSize) != keyFileSize)
    {
        fprintf (stderr, "Unable to read key file [%s] [%s]\n\n", keyFile, strerror(errno));
        return -6;
    }

    close (keyFileFD);

    // Read plain text file
    struct stat plainTextFileStat;
    if (stat(plainTextFile, & plainTextFileStat) < 0)
    {
        fprintf (stderr, "Invalid plainText file [%s] [%s]\n\n", plainTextFile, strerror(errno));
        return -7;
    }

    plainTextFileSize = plainTextFileStat.st_size;

    if (plainTextFileSize != keyFileSize)
    {
        fprintf (stderr, "key file and plainText file size mismatch! [%u]!=[%u]\n\n", keyFileSize, plainTextFileSize);
        return -8;
    }

    int plainTextFileFD = open(plainTextFile, O_RDONLY);
    if (plainTextFileFD < 0)
    {
        fprintf (stderr, "Unable to open plainText file [%s] [%s]\n\n", plainTextFile, strerror(errno));
        return -9;
    }

    plainTextFileData = (uint8_t *)malloc (plainTextFileSize);
    if (read(plainTextFileFD, plainTextFileData, plainTextFileSize) != plainTextFileSize)
    {
        fprintf (stderr, "Unable to read plainText file [%s] [%s]\n\n", plainTextFile, strerror(errno));
        return -10;
    }

    close (plainTextFileFD);

    // Data is loaded and sizes match.
    // Create payload and send to server

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

    uint32_t clientMagic = OTP_ENC_MAGIC;
    send(clientSocket, &clientMagic, sizeof (clientMagic), 0);
    uint32_t serverMagic = 0;
    recv(clientSocket, &serverMagic, sizeof (serverMagic), 0);
    fprintf(stderr, "Server authenticated [0x%08x]\n", serverMagic);
    fflush(stderr);

	close(clientSocket); // Close the socket
	return 0;
}
