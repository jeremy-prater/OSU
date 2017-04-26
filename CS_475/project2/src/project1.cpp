////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 1 - Numeric Integration
//
// Jeremy Prater
//

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "project2.h"
#include "CSVLogger.hpp"

static const char * dataLog = "./project2.csv";
static const char * dataSchema = "numt, mode, chunksize";

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

    unsigned int NUMT = atoi (argv[1]);
    const char * MODE = argv[2];
    unsigned int CHUNKSIZE = atoi (argv[3]);

#ifndef _OPENMP
    printf("OpenMP is not supported here -- sorry.\n" );
    return 1;
#endif

    omp_set_num_threads(NUMT);
    printf("Using %d threads.\t%s scheduling.\tChunksize: %u\t", NUMT, MODE, CHUNKSIZE);
    double totalTime = 0;
    
    
    printf ("-> MegaMults/sec: %f ", totalTime);
    CSVLogger::WriteLog("%u, %u, %s, %f", NUMT, CHUNKSIZE, MODE, totalTime);
    CSVLogger::CloseLogFile();
}


