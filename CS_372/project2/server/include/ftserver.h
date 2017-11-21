#include <stdint.h>

typedef struct
{
    uint16_t dataPort;
    uint8_t command;
    uint16_t payloadLength;
    char payload[];
} ftserverCommandHeader;