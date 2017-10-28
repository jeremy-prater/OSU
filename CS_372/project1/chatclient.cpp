#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <string>
#include <iostream>

void CriticalError(const char *errorMessage)  /* Error handling function */
{
    printf ("Error! [%s]\n", errorMessage);
    exit (-1);
}

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in serverAddress;
    unsigned short serverPort;
    char *serverHost;
    std::string outgoing;
    std::string handle;

    if (argc != 3)
    {
       fprintf(stderr, "Usage: %s <Server IP> <Server Port>\n", argv[0]);
       exit(-1);
    }

    serverHost = argv[1];
    serverPort = atoi(argv[2]);

    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        CriticalError("socket() failed");
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(serverHost);
    serverAddress.sin_port        = htons(serverPort);

    printf ("Connecting to %s:%d\n", serverHost, serverPort);
    if (connect(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
    {
        CriticalError("connect() failed");
    }

    printf ("Enter handle : ");

    std::cin >> handle;
    handle = handle.substr (0,10);

    char running = 1;

    while (running)
    {
        std::cout << handle.c_str() << ">";

        std::cin >> outgoing;

        if (outgoing.compare("/quit") == 0)
        {
            running = 0;
            break;
        }
;
        if (send(sock, outgoing.c_str(), outgoing.length(), 0) != outgoing.length())
        {
            CriticalError("send() sent a different number of bytes than expected");
        }
    }

    close(sock);
    exit(0);
}