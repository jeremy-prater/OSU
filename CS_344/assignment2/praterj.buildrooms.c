///////////////////////////////////////////////////////
//
// CS 344 - Assignment 2 - Jeremy Prater
//
// Build Rooms
//

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "praterj.adventure.h"

static const char * roomNames[MAX_ROOMS] = {
    "Great Hall",
    "Workshop",
    "Kitchen",
    "Blacksmith",
    "Kitchen",
    "Bathroom",
    "Game room",
    "Garage",
    "Basement",
    "Garden"
};

static room_t roomData[NUM_ROOMS];
static room_t * startRoom = 0;
static room_t * endRoom = 0;
static int totalLinks = 0;

void CreateRooms(room_t * rooms)
{
    srand (time(NULL));
    memset (roomData, 0, sizeof (roomData));
    int roomCreationCount = 0;
    while (roomCreationCount < NUM_ROOMS)
    {
        int newRoomIndex = -1;
        while (newRoomIndex == -1)
        {
            newRoomIndex = rand() % MAX_ROOMS;
            // Check if room is already used...
            for (int checkIndex = 0; checkIndex < NUM_ROOMS; checkIndex++)
            {
                if (rooms[checkIndex].roomCreated)
                {
                    if (strcmp (rooms[checkIndex].roomName, roomNames[newRoomIndex]) == 0)
                    {
                        // Uh, oh. That room is already created. Try again
                        newRoomIndex = -1;
                        break;
                    }
                }
            }
        }

        if (rooms[roomCreationCount].roomCreated)
        {
            continue;
        }
        else
        {
            rooms[roomCreationCount].roomName = roomNames[newRoomIndex];
            snprintf (rooms[roomCreationCount].roomFile, MAX_ROOM_PATH, "%s.room", rooms[roomCreationCount].roomName);
            printf ("Created room [%s] with file name [%s]\n", rooms[roomCreationCount].roomName, rooms[roomCreationCount].roomFile);
            rooms[roomCreationCount].roomCreated = 1;
            rooms[roomCreationCount].roomType = ROOM_MID;
            roomCreationCount++;
        }
    }
    int startRoomIndex = rand() % NUM_ROOMS;
    int endRoomIndex = startRoomIndex;
    while (endRoomIndex == startRoomIndex)
    {
        endRoomIndex = rand() % NUM_ROOMS;
    }
    startRoom = &rooms[startRoomIndex];
    endRoom = &rooms[endRoomIndex];
    startRoom->roomType = ROOM_START;
    endRoom->roomType = ROOM_END;
}

int FindEmptyRoomSlot(room_t * room)
{
    for (int connectionIndex = 0; connectionIndex < NUM_CONNECTIONS; connectionIndex++)
    {
        if (!room->roomConnections[connectionIndex])
        {
            return connectionIndex;
        }
    }
    return -1;
}

int CreateLink(room_t * rooms, int A, int B)
{
    if (A == B)
    {
        return 0;
    }

    for (int testRoomIndexA = 0; testRoomIndexA < NUM_CONNECTIONS; testRoomIndexA++)
    {
        for (int testRoomIndexB = 0; testRoomIndexB < NUM_CONNECTIONS; testRoomIndexB++)
        {
            // Check if room B is already connected to room A
            if (
                (rooms[A].roomConnections[testRoomIndexA]) &&
                (rooms[B].roomConnections[testRoomIndexB]) &&
                (rooms[A].roomConnections[testRoomIndexA] == rooms[B].roomConnections[testRoomIndexB])
                )
            {
                // No good, the rooms are already connected...
                /*printf ("[%s] is already connected to [%s] [%p]==[%p]\n",
                    rooms[A].roomName,
                    rooms[B].roomName,
                    rooms[A].roomConnections[testRoomIndexA],
                    rooms[B].roomConnections[testRoomIndexB]);*/
                return 0;
            }
        }
    }
    // Find empty slot and connect rooms
    int aIndex = FindEmptyRoomSlot(&rooms[A]);
    int bIndex = FindEmptyRoomSlot(&rooms[B]);
    rooms[A].roomConnections[aIndex] = (struct room_t*)&rooms[B];
    rooms[B].roomConnections[bIndex] = (struct room_t*)&rooms[A];
    rooms[A].numConnections++;
    rooms[B].numConnections++;
    printf ("Connecting [%s] to [%s] [%p]=[%p]\n",
        rooms[A].roomName,
        rooms[B].roomName,
        rooms[A].roomConnections[aIndex],
        rooms[B].roomConnections[bIndex]);

    totalLinks++;
    return 1;
}

void LinkRooms(room_t * rooms)
{
    int linking = 1;
    while (linking)
    {
        int minLinks = NUM_ROOMS;
        for (int roomIndex = 0; roomIndex < NUM_ROOMS; roomIndex++)
        {
            // Generate a connecting room index
            int A = roomIndex;
            int B = -1;
            int searching = 1;
            B = rand() % NUM_ROOMS;
            if (B != A)
            {
                // No rooms connect to self
                if (CreateLink(rooms, A, B))
                {
                    minLinks = MIN(minLinks, rooms[A].numConnections);
                    minLinks = MIN(minLinks, rooms[B].numConnections);
                }
            }
        }
        if (minLinks >= 3)
        {
            linking = 0;
        }
    }
}

int CheckConnectivity(room_t * start, room_t * end)
{
    // Recurisive functions! Yay!
    start->roomChecked = 1;
    if (start == end)
    {
        return 1;
    }

    int foundIt = 0;
    for (int roomIndex = 0; roomIndex < NUM_CONNECTIONS; roomIndex++)
    {
        if (!(room_t*)start->roomConnections[roomIndex])
        {
            continue;
        }

        if (!((room_t*)start->roomConnections[roomIndex])->roomChecked)
        {
            foundIt |= CheckConnectivity((room_t*)start->roomConnections[roomIndex], end);
        }
    }
    return foundIt;
}

void SaveRoom(room_t * room)
{
    printf ("Saving file [%s]\n", room->roomFile);
    FILE * outFile = fopen(room->roomFile, "w");
    fprintf (outFile, "ROOM NAME: %s\n", room->roomName);
    
    for (int connectionIndex = 0; connectionIndex < NUM_CONNECTIONS; connectionIndex++)
    {
        if (room->roomConnections[connectionIndex])
        {
            fprintf (outFile, "CONNECTION %d: %s\n", connectionIndex + 1, ((room_t*)room->roomConnections[connectionIndex])->roomName);
        }
    }

    switch (room->roomType)
    {
        case ROOM_START:
        fprintf (outFile, "ROOM TYPE: START_ROOM\n");
        break;
        case ROOM_MID:
        fprintf (outFile, "ROOM TYPE: MID_ROOM\n");
        break;
        case ROOM_END:
        fprintf (outFile, "ROOM TYPE: END_ROOM\n");
        break;
    }
    
    fclose(outFile);
}

void SaveRooms(room_t * rooms)
{
    char directory[64];
    snprintf (directory, MAX_ROOM_PATH, "./praterj.rooms.%d", getpid());
    mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    chdir (directory);
    for (int roomIndex = 0; roomIndex < NUM_ROOMS; roomIndex++)
    {
        SaveRoom (&rooms[roomIndex]);
    }
    chdir ("..");
}

int main(int argc, char * argv[])
{
    CreateRooms(roomData);
    LinkRooms (roomData);
    while (!CheckConnectivity(startRoom, endRoom))
    {
        CreateLink(roomData, rand() % NUM_ROOMS, rand() % NUM_ROOMS);
    }
    printf ("Total room connections [%d]\n", totalLinks);
    SaveRooms (roomData);

    return 0;
}
