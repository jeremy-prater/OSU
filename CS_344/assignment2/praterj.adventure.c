///////////////////////////////////////////////////////
//
// CS 344 - Assignment 2 - Jeremy Prater
//
// Adventure Game!
//

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "praterj.adventure.h"
#include <dirent.h>

char gameDirectory[64];

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

void LoadRoom(char * roomFile)
{
    printf ("Loading room [%s]\n", roomFile);
}

void LoadGameData()
{
    DIR * directoryScanner = opendir(gameDirectory);
    struct dirent * currentDirectory;
    while ((currentDirectory = readdir (directoryScanner)))
    {
        if (strstr(currentDirectory->d_name, ".room") != NULL)
        {
            LoadRoom (currentDirectory->d_name);
        }
    }
    closedir (directoryScanner);
}



int main(int argc, char * argv[])
{
    memset (gameDirectory, 0, sizeof (gameDirectory));
    FindNewestGameDir();
    if (strlen(gameDirectory) == 0)
    {
        printf("No valid game directories found! run praterj.buildsrooms first\n");
        return -1;
    }
    LoadGameData();
    return 0;
}
