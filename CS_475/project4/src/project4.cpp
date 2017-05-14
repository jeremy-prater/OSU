////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 4 - Control Threads
//
// Jeremy Prater
//

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "project4.h"
#include "CSVLogger.hpp"
#include <stdlib.h>

static const char * dataLog = "./project4.csv";


const float GRAIN_GROWS_PER_MONTH   = 8.0;
const float ONE_DEER_EATS_PER_MONTH = 0.5;

const float AVG_PRECIP_PER_MONTH    = 6.0;	// average
const float AMP_PRECIP_PER_MONTH    = 6.0;	// plus or minus
const float RANDOM_PRECIP           = 2.0;	// plus or minus noise

const float AVG_TEMP                = 50.0;	// average
const float AMP_TEMP                = 20.0;	// plus or minus
const float RANDOM_TEMP             = 10.0;	// plus or minus noise

const float MIDTEMP                 = 40.0;
const float MIDPRECIP               = 10.0;

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

    //const unsigned int NUMT = atoi (argv[1]);
    //const unsigned int NUMPADDING = atoi(argv[2]);
    //const unsigned int USEFIX2 = atoi(argv[3]);

#ifndef _OPENMP
    printf("OpenMP is not supported here -- sorry.\n" );
    return 1;
#endif

    bool running = true;

    omp_set_num_threads(4);	// same as # of sections
    #pragma omp parallel sections
    {
        while(running)
        {
            #pragma omp section
            {
                GrainDeer();
            }

            #pragma omp section
            {
                Grain();
            }

            #pragma omp section
            {
                Watcher();
            }

            #pragma omp section
            {
                HMI();
            }
        }
    }

    CSVLogger::WriteLog("%u, %u, %u, %f", NUMT, NUMPADDING, USEFIX2, megaAddsSec);
    CSVLogger::CloseLogFile();
}


