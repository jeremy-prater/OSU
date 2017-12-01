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

void GetServerResponse(int argc, char *argv[], uint32_t serverMagicTest, uint32_t clientMagic)
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
        printf ("%s [plain text file] [key file] [server port]\n", argv[0]);
        exit(-1);
    }

    if (sscanf (argv[1], "%s", plainTextFile) != 1)
    {
        printf ("Invalid text file [%s]", argv[1]);
        exit(-1);
    }
    if (sscanf (argv[2], "%s", keyFile) != 1)
    {
        printf ("Invalid key file [%s]", argv[1]);
        exit(-2);
    }
    if ((sscanf (argv[3], "%d", &clientPort) != 1) || (clientPort < 0) || (clientPort > 0xFFFF))
    {
        printf ("Invalid port!! Must be 0-65535 [%d]\n\n", clientPort);
        exit(-3);
    }

    // Read key file
    struct stat keyFileStat;
    if (stat(keyFile, & keyFileStat) < 0)
    {
        printf ("Invalid key file [%s] [%s]\n\n", keyFile, strerror(errno));
        exit(-4);
    }

    keyFileSize = keyFileStat.st_size - 1;
    int keyFileFD = open(keyFile, O_RDONLY);
    if (keyFileFD < 0)
    {
        printf ("Unable to open key file [%s] [%s]\n\n", keyFile, strerror(errno));
        exit(-5);
    }

    keyFileData = (uint8_t *)malloc (keyFileSize);
    if (read(keyFileFD, keyFileData, keyFileSize) != keyFileSize)
    {
        printf ("Unable to read key file [%s] [%s]\n\n", keyFile, strerror(errno));
        exit(-6);
    }

    close (keyFileFD);

    // Read plain text file
    struct stat plainTextFileStat;
    if (stat(plainTextFile, & plainTextFileStat) < 0)
    {
        printf ("Invalid plainText file [%s] [%s]\n\n", plainTextFile, strerror(errno));
        exit(-7);
    }

    plainTextFileSize = plainTextFileStat.st_size - 1;

    if (plainTextFileSize > keyFileSize)
    {
        printf ("key file and plainText file size mismatch! [%u] < [%u]\n\n", keyFileSize, plainTextFileSize);
        exit(1);
    }

    int plainTextFileFD = open(plainTextFile, O_RDONLY);
    if (plainTextFileFD < 0)
    {
        printf ("Unable to open plainText file [%s] [%s]\n\n", plainTextFile, strerror(errno));
        exit(-9);
    }

    plainTextFileData = (uint8_t *)malloc (plainTextFileSize);
    if (read(plainTextFileFD, plainTextFileData, plainTextFileSize) != plainTextFileSize)
    {
        printf ("Unable to read plainText file [%s] [%s]\n\n", plainTextFile, strerror(errno));
        exit(-10);
    }

    close (plainTextFileFD);

    int index = 0;
    for (index = 0; index < keyFileSize; index++)
    {
        if (!(((keyFileData[index] >= 'A') && (keyFileData[index] <= 'Z')) || (keyFileData[index] == ' ')))
        {
            printf ("Key file [%s] contains invalid characters [%c]\n\n", keyFile ,keyFileData[index]);
            exit (1);
        }
    }
    for (index = 0; index < plainTextFileSize; index++)
    {
        if (!(((plainTextFileData[index] >= 'A') && (plainTextFileData[index] <= 'Z')) || (plainTextFileData[index] == ' ')))
        {
            printf ("Input file [%s] contains invalid characters [%c]\n\n", plainTextFile ,plainTextFileData[index]);
            exit (1);
        }
    }

    // Data is loaded and sizes match.
    // All characters are valid
    // Create payload and send to server

    // Create TCP socket on port
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf (stderr, "Failed to create TCP client socket [%s]\n\n", strerror(errno));
        exit( -errno);
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
        exit(-errno);
    }
    ssize_t socketRes = 0;
    socketRes = send(clientSocket, &clientMagic, sizeof (clientMagic), 0);
    if ((socketRes < 0) || (socketRes != sizeof(clientMagic)))
    {
        fprintf (stderr, "Failed to send client magic [%s]\n", strerror(errno));
        exit(-errno);
    }
    uint32_t serverMagic = 0;
    socketRes = recv(clientSocket, &serverMagic, sizeof (serverMagic), 0);
    if ((socketRes < 0) || (socketRes != sizeof(serverMagic)))
    {
        printf ("Failed to recv server magic. Do not mix otp_enc/otp_dec!\n");
        exit(2);
    }

    if (serverMagic != serverMagicTest)
    {
        // This probably can never happen because the server disconnects as soon as the magic is incorrect.
        printf("Server authenticated failed[0x%08x]!=[0x%08x]!!\n", serverMagic, serverMagicTest);
        printf ("Failed to recv server magic. Do not mix otp_enc/otp_dec!\n");
        exit(2);
    }

    fprintf(stderr, "Server authenticated [0x%08x]\n", serverMagic);

    TransformInput (keyFileData, plainTextFileSize);
    TransformInput (plainTextFileData, plainTextFileSize);

    fprintf(stderr, "Sending key/data size [%u]\n", plainTextFileSize);
    send(clientSocket, &plainTextFileSize, sizeof (plainTextFileSize), 0);

    SendDataLoop (clientSocket, keyFileData, plainTextFileSize);
    SendDataLoop (clientSocket, plainTextFileData, plainTextFileSize);

    uint8_t * resultPayload = (uint8_t *)malloc (plainTextFileSize + 1);
    resultPayload[plainTextFileSize] = 0x00;

    uint32_t originalFileSize = plainTextFileSize;
    uint32_t offset = 0;
    while (plainTextFileSize > 0)
    {
        uint32_t recvSize = plainTextFileSize;
        if (plainTextFileSize > 1000)
        {
            recvSize = 1000;
        }
        ssize_t recvRes = recv(clientSocket, &resultPayload[offset], plainTextFileSize, 0);
        if (recvRes < 0)
        {
            fprintf (stderr, "Failed recv data from daemon [%s]\n", strerror(errno));
            exit (-errno);
        }
        else
        {
            offset += recvRes;
            plainTextFileSize -= recvRes;
        }
    }

    TransformOutput (resultPayload, originalFileSize);

    printf ("%s\n", resultPayload);

    free(keyFileData);
    free(plainTextFileData);
    free(resultPayload);

	close(clientSocket); // Close the socket
}

