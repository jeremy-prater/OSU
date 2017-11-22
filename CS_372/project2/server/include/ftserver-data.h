#ifndef FTSERVER_DATA_H
#define FTSERVER_DATA_H

#include <stdint.h>

uint8_t * GetServerResponse(const char * host, uint16_t clientPort);

#endif // FTSERVER_DATA_H