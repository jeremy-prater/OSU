#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <errno.h>
#include <string.h>

static int serverSocket;

uint8_t * GetServerResponse(const char * host, uint16_t clientPort)
{
    printf ("Connect to ftclient [%s]:[%d]\n", host, clientPort);
    struct hostent *server;
    struct sockaddr_in serverAddress;
    int serverConnection = -1;

    memset (&serverAddress, 0, sizeof (serverAddress));

    // Create TCP socket on port
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("Failed to create TCP server socket [%s]\n\n", strerror(errno));
        exit(-errno);
    }

    server = gethostbyname(host);
    if (server == NULL) {
        printf("Failed to find host [%s]\n", host);
        exit(-4);
    }

    serverAddress.sin_family = AF_INET;
    memcpy (&serverAddress.sin_addr.s_addr, server->h_addr_list[0], server->h_length);
    serverAddress.sin_port = htons(clientPort);

    int retryCounter = 0;
    while (connect(serverSocket, (const struct sockaddr*)&serverAddress, sizeof (serverAddress)) < 0)
    {
        sleep(1);
        retryCounter++;
        if (retryCounter == 5)
        {
            printf("Failed to connect to ftClient [%s]\n\n", strerror(errno));
            exit(-errno);
        }
    }

    printf("Connected to data port [%s]:[%d]\n", host, clientPort);
    fflush(stdout);

    uint32_t payloadSize = 0;

    recv(serverSocket, &payloadSize, sizeof (uint32_t), 0);
    payloadSize = ntohs(payloadSize);
    printf ("Data recv! [%d]\n", payloadSize);
    uint8_t * recvData = (uint8_t *)malloc (payloadSize);
    recv(serverSocket, recvData, payloadSize, 0);
    printf("Data: [%s]\n", recvData);

    return NULL;
}
