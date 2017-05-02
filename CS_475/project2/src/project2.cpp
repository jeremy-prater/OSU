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
#include <string.h>
#include "project2.h"
#include "CSVLogger.hpp"

static const char * dataLog = "./project2.csv";
static const char * dataSchema = "numt, mode, chunksize";

static const unsigned int ARRAYSIZE = (32 * 1024);
static long int numMuled = (long int)ARRAYSIZE * (long int)(ARRAYSIZE-1) / 2;

static float Array[ARRAYSIZE];

float fRand(float low, float high)
{
	float r = (float)rand();		// 0 - RAND_MAX
	return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}

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

    unsigned int NUMT = atoi (argv[1]);
    const char * MODE = argv[2];
    unsigned int CHUNKSIZE = atoi (argv[3]);

#ifndef _OPENMP
    printf("OpenMP is not supported here -- sorry.\n" );
    return 1;
#endif

    omp_set_num_threads(NUMT);
    printf("Using %d threads.\t", NUMT);

    /////////////////////////////////////////////////////////
    //
    // Generate array of data
    // Might as well parallize this also to speed up!
    //

    #pragma omp parallel for default(none), shared(Array)
    for(unsigned int index = 0; index < ARRAYSIZE; index++)
    {
        Array[index] = fRand (-1.0f, 1.0f);
    }


    printf("%s scheduling.\tChunksize: %u\t", MODE, CHUNKSIZE);
    
    omp_sched_t schedType = omp_sched_auto;
    if (strcmp (MODE, "static") == 0)
    {
        schedType = omp_sched_static;
    }
    else if (strcmp (MODE, "dynamic") == 0)
    {
        schedType = omp_sched_dynamic;
    }
    else
    {
        exit (-1);
    }

    omp_set_schedule(schedType, CHUNKSIZE);
    double time0 = omp_get_wtime();
    double prod = 1.0f;
    #pragma omp parallel for default(none) shared(Array) reduction (*:prod) collapse(2)
    for (unsigned int outerLoop = 0; outerLoop < ARRAYSIZE; outerLoop++)
    {
        prod = 1.0f;

        for (unsigned int innerLoop = 0; innerLoop < outerLoop; innerLoop++)
        {
            prod *= Array[innerLoop];
        }
    }
    double megaMultsSec = ((double)numMuled / (omp_get_wtime() - time0)) /  1000000.;

    printf ("-> MegaMults/sec: %f\n", megaMultsSec);
    CSVLogger::WriteLog("%u, %u, %s, %f", NUMT, CHUNKSIZE, MODE, megaMultsSec);
    CSVLogger::CloseLogFile();
}


