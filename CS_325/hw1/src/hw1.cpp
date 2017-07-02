////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 325 - Homework 1
//
// Jeremy Prater
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "CSVLogger.hpp"
#include <stdlib.h>

static const char * dataLog = "./hw1.csv";
static const char * dataSchema = "NUM_ELEMENTS,INSERT_METHOD,RUNTIME";

int main( int argc, char *argv[ ] )
{
    if (argc != 4)
    {
        printf("Incorrect number of arguments...\n");
        exit(-1);
    }

    if (CSVLogger::OpenLogFile(dataLog))
    {
        CSVLogger::WriteLog(dataSchema);
    }

    const unsigned int USE_DATA = atoi(argv[1]);
    const unsigned int NUM_ELEMENTS = atoi (argv[2]);

    printf ("-> USE_DATA: %d\t", USE_DATA);
    printf ("-> Elements: %d\t", NUM_ELEMENTS);
    CSVLogger::WriteLog("%d, %d, %d, %d, %f, %f",
    //DEVICE_NAME,
    NUM_ELEMENTS,
    LOCAL_SIZE,
    OP_MODE,
    NUM_WORK_GROUPS,
    megaMultsSecBest,
    megaMultsSecAvg);


    CSVLogger::CloseLogFile();

}
