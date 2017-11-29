#include "common.h"

#include <stdio.h>

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