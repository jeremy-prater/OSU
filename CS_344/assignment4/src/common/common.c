#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


void TransformInput (uint8_t * data, uint32_t size)
{
    uint32_t index = 0;
    for (index = 0; index < size; index++)
    {
        if (data[index] == 0x20)
        {
            data[index] = 0x5B;
        }
        data[index] -= 0x41;
    }
}

void TransformOutput (uint8_t * data, uint32_t size)
{
    uint32_t index = 0;
    for (index = 0; index < size; index++)
    {
        data[index] += 0x41;
        if (data[index] == 0x5B)
        {
            data[index] = 0x20;
        }
    }
}
uint8_t * GetDataRecvLoop(int socket, uint32_t size)
{
    uint8_t * payload = (uint8_t *)malloc(size);
    uint32_t offset = 0;
    fprintf (stderr, " -- Server Recv Start [%d]\n", size);
    while (size > 0)
    {
        uint32_t recvSize = size;
        if (recvSize > 1000)
        {
            recvSize = 1000;
        }
        fprintf (stderr, " -- Server Recv progress [%d]\n", offset);
        offset += recv(socket, &payload[offset], recvSize, 0);
        if (offset < 0)
        {
            fprintf (stderr, "Client recv data failed [%s]\n" ,strerror(errno));
            exit (-errno);
        }

        size -= offset;
    }
    fprintf (stderr, " -- Server Recv progress [%d]\n", offset);
    return payload;
}

uint8_t * SendDataLoop(int socket, uint8_t * data, uint32_t size)
{
    fprintf (stderr, " -- Server Send Start [%d]\n", size);
    uint32_t offset = 0;
    while (size > 0)
    {
        uint32_t recvSize = size;
        if (recvSize > 1000)
        {
            recvSize = 1000;
        }
        fprintf (stderr, " -- Server Send progress [%d]\n", offset);
        ssize_t sendRes = send(socket, &data[offset], recvSize, 0);
        if (sendRes < 0)
        {
            fprintf (stderr, "Client send data failed [%s]\n" ,strerror(errno));
            exit (-errno);
        }
        else
        {
            offset += sendRes;
        }

        size -= offset;
    }
    fprintf (stderr, " -- Server Send progress [%d]\n", offset);
}
