////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 5 - SIMD
//
// Jeremy Prater
//

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "simd.p5.h"
#include "nonSimd.h"
#include "CSVLogger.hpp"
#include <stdlib.h>
#include "Randomizer.hpp"

static const char * dataLog = "./project5.csv";
static const char * dataSchema = "useSIMD, doReduction, arraySize, totalTime, megaOpsSec";

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

    const unsigned int useSIMD = atoi (argv[1]);
    const unsigned int doReduction = atoi(argv[2]);
    const unsigned int arraySize = atoi(argv[3]);
    float * ArrayA = (float*) aligned_alloc (64, arraySize);
    float * ArrayB = (float*) aligned_alloc (64, arraySize);
    float * ArrayC = (float*) aligned_alloc (64, arraySize);
    const unsigned int numFloats = arraySize / 4;

#ifndef _OPENMP
    printf("OpenMP is not supported here -- sorry.\n" );
    return 1;
#endif

    if (CSVLogger::OpenLogFile(dataLog))
    {
        CSVLogger::WriteLog(dataSchema);
    }

    unsigned int seed = Randomizer::GetTimeBasedSeed();
    for (int index = 0; index < numFloats; index++)
    {
        ArrayA[index] = Randomizer::Random(&seed, -1, 1);
        ArrayB[index] = Randomizer::Random(&seed, -1, 1);
    }

    const double time0 = omp_get_wtime();

    if (useSIMD)
    {
        if (doReduction)
        {
            SimdMulSum(ArrayA, ArrayB, numFloats);
        }
        else
        {
            SimdMul(ArrayA, ArrayB, ArrayC, numFloats);
        }
    }
    else
    {
        if (doReduction)
        {
            MulSum(ArrayA, ArrayB, numFloats);
        }
        else
        {
            Mul(ArrayA, ArrayB, ArrayC, numFloats);
        }
    }

    double totalTime = omp_get_wtime() - time0;
    double megaOpsSec = (arraySize / totalTime) / 1000000;
    printf ("-> Use SIMD: %d\t", useSIMD);
    printf ("-> Do Reduction: %d\t", doReduction);
    printf ("-> ArraySize: %08x\t", arraySize);
    printf ("-> Time: %f\t", totalTime);
    printf ("-> MegaOps/Sec: %f\n", megaOpsSec);
    CSVLogger::WriteLog("%d, %d, %d, %f, %f", useSIMD, doReduction, arraySize, totalTime, megaOpsSec);

    CSVLogger::CloseLogFile();
    free (ArrayA);
    free (ArrayB);
    free (ArrayC);
}


