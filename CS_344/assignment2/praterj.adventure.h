///////////////////////////////////////////////////////
//
// CS 344 - Assignment 2 - Jeremy Prater
//
// Adventure header file
//

#ifndef CS344_ADVENTURE_H
#define CS344_ADVENTURE_H

#define NUM_ROOMS 7
#define MAX_ROOMS 10
#define NUM_CONNECTIONS 6
#define NUM_DEFAULT_CONNECTIONS 3
#define MAX_ROOM_PATH 256

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef enum
{
    ROOM_START,
    ROOM_MID,
    ROOM_END
} ROOM_TYPE;

typedef struct
{
    const char * roomName;
    char roomFile[MAX_ROOM_PATH];
    struct room_t * roomConnections[NUM_CONNECTIONS];
    int roomCreated;
    int roomChecked;
    int numConnections;
    ROOM_TYPE roomType;
} room_t;

#endif // CS344_ADVENTURE_H