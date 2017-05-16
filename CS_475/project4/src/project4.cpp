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
#include "project4.hpp"
#include "GraindeerController.hpp"
#include "CSVLogger.hpp"
#include <stdlib.h>

static const char * dataLog = "./project4.csv";

int main( int argc, char *argv[ ] )
{
#ifndef _OPENMP
    printf("OpenMP is not supported here -- sorry.\n" );
    return 1;
#endif

    SystemState systemState;
    GraindeerController::SetInitialState(&systemState);

    omp_set_num_threads(4);	// same as # of sections
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            GraindeerController::GrainDeer(&systemState);
        }

        #pragma omp section
        {
            GraindeerController::GrainGrowth(&systemState);
        }

        #pragma omp section
        {
            GraindeerController::Watcher(&systemState);
        }

        #pragma omp section
        {
            GraindeerController::HMI(&systemState);
        }
    }
}


