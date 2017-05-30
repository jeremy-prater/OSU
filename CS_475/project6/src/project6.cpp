////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 6 - OpenCL
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
#include "OpenCL.hpp"

static const char * dataLog = "./project6.csv";
static const char * dataSchema = "";

static const int iterations = 10;

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

    const unsigned int NUM_ELEMENTS = atoi (argv[1]) * 1024 * 1024;
    const unsigned int LOCAL_SIZE = atoi(argv[2]);
    const unsigned int OP_MODE = atoi(argv[3]);
    const unsigned int NUM_WORK_GROUPS = NUM_ELEMENTS / LOCAL_SIZE;
    float * ArrayA = (float*) aligned_alloc (64, NUM_ELEMENTS * sizeof (float));
    float * ArrayB = (float*) aligned_alloc (64, NUM_ELEMENTS * sizeof (float));
    float * ArrayC = (float*) aligned_alloc (64, NUM_ELEMENTS * sizeof (float));

    if (CSVLogger::OpenLogFile(dataLog))
    {
        CSVLogger::WriteLog(dataSchema);
    }

    // Setup data
    OpenCL openCL;
    openCL.InitOpenCL();

    for (int iteration = 0; iteration < iterations; iteration++)
    {
        const double time0 = omp_get_wtime();

        double curTime = omp_get_wtime() - time0;
        avgTime += curTime;
        if ((iteration == 0) || (curTime < bestTime))
        {
            bestTime = curTime;
        }
    }

    avgTime /= iterations;

    double megaMultsSecBest = (arraySize / bestTime) / 1000000;
    double megaMultsSecAvg = (arraySize / avgTime) / 1000000;
    /*printf ("-> Use SIMD: %d\t", useSIMD);
    printf ("-> Do Reduction: %d\t", doReduction);
    printf ("-> ArraySize: %08x\t", arraySize);
    printf ("-> MegaMults/Sec(best): %f\t", megaMultsSecBest);
    printf ("-> MegaMults/Sec(avg): %f ", megaMultsSecAvg);
    printf ("-> time (best): %.10e ", bestTime);
    printf ("-> time (avg): %.10e\n", avgTime);
    CSVLogger::WriteLog("%d, %d, %d, %f, %f, %.10e, %.10e", useSIMD, doReduction, arraySize, megaMultsSecAvg, megaMultsSecBest, avgTime, bestTime);*/

    CSVLogger::CloseLogFile();

    free (ArrayA);
    free (ArrayB);
    free (ArrayC);
}


