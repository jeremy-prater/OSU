///////////////////////////////////////////////////////
//
// CS 344 - Assignment 2 - Jeremy Prater
//
// Adventure Game!
//

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "praterj.adventure.h"
#include <dirent.h>
#include <pthread.h>

char gameDirectory[64];
room_t rooms[NUM_ROOMS];
room_t * startRoom;
room_t * endRoom;
room_t * currentRoom;
pthread_t timeThread;
pthread_mutex_t timeMutex = PTHREAD_MUTEX_INITIALIZER;
int timeThreadRunning = 1;
volatile int timerRunning = 0;

int CheckTimeDiff (const struct timespec lhs, const struct timespec rhs)
{
    if (lhs.tv_sec == rhs.tv_sec)
        return lhs.tv_nsec > rhs.tv_nsec;
    else
        return lhs.tv_sec > rhs.tv_sec;
}

char * FindNewestGameDir()
{
    DIR * directoryScanner = opendir(".");
    struct dirent * currentDirectory;
    struct timespec newestDirectory;
    memset (&newestDirectory, 0, sizeof (newestDirectory));

    while ((currentDirectory = readdir (directoryScanner)))
    {
        if ((currentDirectory->d_type == DT_DIR) && (strstr(currentDirectory->d_name, "praterj.rooms") != NULL))
        {
            struct stat dirStat;
            stat (currentDirectory->d_name, &dirStat);
            if (CheckTimeDiff(dirStat.st_mtim, newestDirectory))
            {
                strcpy(gameDirectory, currentDirectory->d_name);
                memcpy (&newestDirectory, &dirStat.st_mtim, sizeof (struct timespec));
            }
        }
    }
    printf ("Using game directory [%s]\n", gameDirectory);
    closedir (directoryScanner);
}

void LoadRoom(int roomIndex, char * roomFileName)
{
    char localFileName[128];
    snprintf(localFileName, 128, "%s/%s", gameDirectory, roomFileName);
    char localBuffer[128];
    printf ("Loading room [%s]\n", localFileName);
    FILE * roomFile = fopen(localFileName, "r");
    if (roomFile == NULL)
    {
        printf ("Error Loading room [%s] [%s]\n", roomFileName, strerror(errno));
        exit(-2);
    }
    fgets(localBuffer, 128, roomFile);
    do
    {
        localBuffer[strlen(localBuffer) - 1] = 0x00;
        if (strstr(localBuffer, "ROOM NAME"))
        {
            char * token = strtok (localBuffer, ":");
            token = strtok (NULL, ":");
            token++;
            rooms[roomIndex].roomName = strdup(token);
            printf ("Room [%d] Name [%s]\n", roomIndex, rooms[roomIndex].roomName);
        }

        if (strstr(localBuffer, "CONNECTION"))
        {
            char * token = strtok (localBuffer, " ");
            token = strtok (NULL, " ");
            token[1] = 0x00;
            int connectionIndex = atoi(token);
            token+=3;
            rooms[roomIndex].roomConnectionIDs[connectionIndex] = strdup(token);
            printf ("Room [%d] Connection [%d][%s]\n", roomIndex, connectionIndex, rooms[roomIndex].roomConnectionIDs[connectionIndex]);
        }


        if (strstr(localBuffer, "ROOM TYPE"))
        {
            char * token = strtok (localBuffer, ":");
            token = strtok (NULL, ":");
            token++;
            if (strstr(token, "START_ROOM"))
            {
                rooms[roomIndex].roomType = ROOM_START;
                startRoom = &rooms[roomIndex];
                currentRoom = startRoom;
            }
            if (strstr(token, "MID_ROOM"))
            {
                rooms[roomIndex].roomType = ROOM_MID;
            }
            if (strstr(token, "END_ROOM"))
            {
                rooms[roomIndex].roomType = ROOM_END;
                endRoom = &rooms[roomIndex];
            }
            printf ("Room [%d] Type [%d]\n", roomIndex, rooms[roomIndex].roomType);
        }

        fgets(localBuffer, 128, roomFile);
    } while (!feof(roomFile));
    fclose(roomFile);
}

void LoadGameData()
{
    DIR * directoryScanner = opendir(gameDirectory);
    struct dirent * currentDirectory;
    int roomIndex = 0;
    while ((currentDirectory = readdir (directoryScanner)))
    {
        if (strstr(currentDirectory->d_name, ".room") != NULL)
        {
            LoadRoom (roomIndex++, currentDirectory->d_name);
        }
    }
    closedir (directoryScanner);
}

room_t * FindRoom(const char * name)
{
    int roomIndex = 0;
    for (roomIndex = 0; roomIndex < NUM_ROOMS; roomIndex++)
    {
        if (strcmp (name, rooms[roomIndex].roomName) == 0)
        {
            return &rooms[roomIndex];
        }
    }
    return NULL;    
}

void LinkRooms()
{
    int roomIndex = 0;
    for (roomIndex = 0; roomIndex < NUM_ROOMS; roomIndex++)
    {
        room_t * currentRoom = &rooms[roomIndex];
        int connectionIndex = 0;
        for (connectionIndex = 0; connectionIndex < NUM_CONNECTIONS; connectionIndex++)
        {
            if (rooms[roomIndex].roomConnectionIDs[connectionIndex])
            {
                rooms[roomIndex].roomConnections[connectionIndex] = (struct room_t *)FindRoom(rooms[roomIndex].roomConnectionIDs[connectionIndex]);
                printf ("Linking [%s]->[%s]\n", rooms[roomIndex].roomName, ((room_t *)rooms[roomIndex].roomConnections[connectionIndex])->roomName);
            }
        }
    }
}

int runGame()
{
    printf ("CURRENT LOCATION: %s\n", currentRoom->roomName);

    char roomConnections[512];
    char userInput[128];
    memset (roomConnections, 512, 0);
    char * roomConnectionStringPtr = roomConnections;
    int connectionIndex = 0;
    for (connectionIndex = 0; connectionIndex < NUM_CONNECTIONS; connectionIndex++)
    {
        if (currentRoom->roomConnections[connectionIndex])
        {
            const char * connectorName = ((room_t *)currentRoom->roomConnections[connectionIndex])->roomName;
            int stringLength = strlen(connectorName);
            memcpy (roomConnectionStringPtr, connectorName, stringLength);
            roomConnectionStringPtr += stringLength;
            *roomConnectionStringPtr = ',';
            roomConnectionStringPtr++;
            *roomConnectionStringPtr = ' ';
            roomConnectionStringPtr++;
        }
    }
    roomConnectionStringPtr--;
    roomConnectionStringPtr--;
    *roomConnectionStringPtr = '.';
    roomConnectionStringPtr++;
    *roomConnectionStringPtr = 0x00;
    printf ("POSSIBLE CONNECTIONS: %s\n", roomConnections);
    printf ("WHERE TO? >");
    fgets(userInput, 128, stdin);
    userInput[strlen(userInput) - 1] = 0x00;

    int foundRoom = 0;
    if (strcmp (userInput, "time") == 0)
    {
        pthread_mutex_unlock (&timeMutex);
        timerRunning = 1;
        while (timerRunning);
        pthread_mutex_lock (&timeMutex);
        return 0;
    }
    else
    {
        int connectionIndex = 0;
        for (connectionIndex = 0; connectionIndex < NUM_CONNECTIONS; connectionIndex++)
        {
            if (currentRoom->roomConnections[connectionIndex])
            {
                if (strcmp (userInput, ((room_t *)currentRoom->roomConnections[connectionIndex])->roomName) == 0)
                {
                    currentRoom = (room_t *)currentRoom->roomConnections[connectionIndex];
                    foundRoom = 1;
                }
            }
        }
    }

    if (!foundRoom)
    {
        printf ("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
        return 0;
    }

    printf ("\n");

    return 1;
}

void * timeFunction(void * context)
{
    while (timeThreadRunning)
    {
        pthread_mutex_lock (&timeMutex);
        if (timeThreadRunning && timerRunning)
        {
            timerRunning = 0;
            time_t now;
            time (&now);
            const struct tm * timeNow = localtime (&now);
            char timeString[128];
            memset (timeString, 0, 128);
            strftime(timeString, 128, "%l:%M%p, %A, %B %d, %Y", timeNow);
            printf ( "\n %s\n\n", timeString);
            FILE * timeFile = fopen ("currentTime.txt", "w");
            if (!timeFile)
            {
                printf ("Failed to create currentTime.txt [%s]", strerror(errno));
                exit (-4);
            }
            timeString[strlen(timeString)] = '\n';
            fwrite(timeString, strlen (timeString), 1, timeFile);
            fclose (timeFile);
          
        }
        pthread_mutex_unlock (&timeMutex);
    }
}

int main(int argc, char * argv[])
{
    pthread_mutex_lock (&timeMutex);
    if (pthread_create(&timeThread, NULL, timeFunction, NULL))
    {
        printf ("Failed to create time worker thread!\n");
        exit (-3);
    }
    memset (gameDirectory, 0, sizeof (gameDirectory));
    memset (rooms, 0, sizeof(room_t) * NUM_ROOMS);
    FindNewestGameDir();
    if (strlen(gameDirectory) == 0)
    {
        printf("No valid game directories found! run praterj.buildsrooms first\n");
        return -1;
    }
    LoadGameData();
    LinkRooms();
    int turnCounter = 0;
    char ** history = (char**)malloc(sizeof (char*));
    while (currentRoom != endRoom)
    {
        int turnStatus = runGame();
        if (turnStatus)
        {
            history = (char**)realloc (history, sizeof (char*) * (turnCounter + 1));
            history[turnCounter] = strdup(currentRoom->roomName);
        }
        turnCounter += turnStatus;
    }
    printf ("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
    printf ("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", turnCounter);
    int historyIndex = 0;
    for (historyIndex = 0; historyIndex < turnCounter; historyIndex++)
    {
        printf("%s\n", history[historyIndex]);
        free (history[historyIndex]);
    }

    free (history);
    int roomIndex = 0;
    for (roomIndex = 0; roomIndex < NUM_ROOMS; roomIndex++)
    {
        free ((void*)rooms[roomIndex].roomName);
        int connectionIndex = 0;
        for (connectionIndex = 0; connectionIndex < NUM_CONNECTIONS; connectionIndex++)
        {
            if (((room_t*)&rooms[roomIndex])->roomConnectionIDs[connectionIndex])
            {
                free ((void*)((room_t*)&rooms[roomIndex])->roomConnectionIDs[connectionIndex]);
            }
        }
    }
    
    timeThreadRunning = 0;
    pthread_mutex_unlock (&timeMutex);
    pthread_join(timeThread, NULL);
    return 0;
}
