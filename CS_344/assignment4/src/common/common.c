#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


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
    while (size > 0)
    {
        uint32_t recvSize = size;
        if (size > 1000)
        {
            recvSize = 1000;
        }
        offset += recv(socket, &payload[offset], size, 0);
        if (offset < 0)
        {
            fprintf (stderr, "Client recv data failed [%s]\n" ,strerror(errno));
            exit (-errno);
        }

        size -= offset;
    }
    return payload;
}
