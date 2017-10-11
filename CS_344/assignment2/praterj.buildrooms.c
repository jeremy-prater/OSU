///////////////////////////////////////////////////////
//
// CS 344 - Assignment 2 - Jeremy Prater
//
// Build Rooms
//

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
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

void CreateRooms(room_t * rooms)
{
    srand (time(NULL));
    memset (roomData, 0, sizeof (rooms));
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
            snprintf (rooms[roomCreationCount].roomFile, MAX_ROOM_PATH, "praterj.rooms.%d.%s", getpid(), rooms[roomCreationCount].roomName);
            printf ("Created room [%s] with file name [%s]\n", rooms[roomCreationCount].roomName, rooms[roomCreationCount].roomFile);
            rooms[roomCreationCount].roomCreated = 1;
            roomCreationCount++;
        }
    }
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
    for (int testRoomIndex = 0; testRoomIndex < NUM_ROOMS; testRoomIndex++)
    {
        // Check if room B is already connected to room A
        if (rooms[B].roomConnections[testRoomIndex] == (struct room_t*)&rooms[A])
        {
            // No good, the rooms are already connected...
            //printf ("[%s] is already connected to [%s]\n", rooms[A].roomName, rooms[B].roomName);
            return 0;
        }
    }
    printf ("Connecting [%s] to [%s]\n", rooms[A].roomName, rooms[B].roomName);
    // Find empty slot and connect rooms
    int aIndex = FindEmptyRoomSlot(&rooms[A]);
    int bIndex = FindEmptyRoomSlot(&rooms[B]);
    rooms[A].roomConnections[aIndex] = (struct room_t*)&rooms[B];
    rooms[B].roomConnections[bIndex] = (struct room_t*)&rooms[A];
    return 1;
}

void LinkRooms(room_t * rooms)
{
    // Starting room is at index 0
    // Ending room is at NUM_ROOMS
    // A tree is probably the best data structure to do this
    // The ending room will be a leaf at the outermost branch
    for (int roomConnectionCount = 0; roomConnectionCount < NUM_DEFAULT_CONNECTIONS; roomConnectionCount++)
    {
        for (int roomIndex = 0; roomIndex < NUM_ROOMS; roomIndex++)
        {
            // Generate a connecting room index
            int A = roomIndex;
            int B = -1;
            int searching = 1;
            while (searching)
            {
                B = rand() % NUM_ROOMS;
                if (B != A)
                {
                    // No rooms connect to self
                    searching = !CreateLink(rooms, A, B);
                }
            }
        }
    }
}

void SaveRooms(room_t * rooms)
{

}

int main(int argc, char * argv[])
{
    CreateRooms(roomData);
    LinkRooms (roomData);
    SaveRooms (roomData);
    return 0;
}
