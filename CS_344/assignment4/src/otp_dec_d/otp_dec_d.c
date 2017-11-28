#include <stdint.h>
#include <memory.h>
#include <stdlib.h>
#include "common.h"

int main (int argc, char * argv[])
{
    CreateServer(argc, argv, OTP_DEC_MAGIC, OTP_DEC_MAGIC);
    exit(0);
}

uint8_t * PreformOTP(uint8_t * keyData, uint8_t * fileData, uint32_t keyDataSize)
{
    uint8_t * resultData = (uint8_t *)malloc(keyDataSize);
    for (uint32_t index = 0; index < keyDataSize; index++)
    {
        resultData[index] = (fileData[index] - keyData[index]) % 27;
    }
    return resultData;
}