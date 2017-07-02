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
#include <time.h>
#include <stdlib.h>

static const char * dataLog = "./hw1.csv";
static const char * dataSchema = "NUM_ELEMENTS,INSERT_METHOD,RUNTIME,RUNTIMEAVG";

static const uint32_t numIterations = 10;

static struct timespec time0;
static struct timespec time1;

int main( int argc, char *argv[ ] )
{
    if (argc != 3)
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
    printf ("-> ELEMENTS: %d\t", NUM_ELEMENTS);
    CSVLogger::WriteLog("%d, %d, %d, %d, %f, %f",
    USE_DATA,
    NUM_ELEMENTS,
    runTime,
    runTimeAvg);


    CSVLogger::CloseLogFile();

}
