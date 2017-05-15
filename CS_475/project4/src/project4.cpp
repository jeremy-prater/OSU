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

    SystemState systemState;
    GraindeerController::GetInitialState(&systemState);

    omp_set_num_threads(4);	// same as # of sections
    #pragma omp parallel sections
    {
        while(running)
        {
            #pragma omp section
            {
                GraindeerController::GrainDeer();
            }

            #pragma omp section
            {
                GraindeerController::Grain();
            }

            #pragma omp section
            {
                GraindeerController::Watcher();
            }

            #pragma omp section
            {
                GraindeerController::HMI();
            }
        }
    }

    CSVLogger::WriteLog("%u, %u, %u, %f", NUMT, NUMPADDING, USEFIX2, megaAddsSec);
    CSVLogger::CloseLogFile();
}


