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
#define MAX_ROOM_PATH 256

typedef struct
{
    const char * roomName;
    char roomFile[MAX_ROOM_PATH];
    struct room_t * roomConnections[NUM_CONNECTIONS];
    int roomCreated;
    int numConnections;
} room_t;

#endif // CS344_ADVENTURE_H