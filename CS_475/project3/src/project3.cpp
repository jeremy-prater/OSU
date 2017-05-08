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
#include "project3.h"
#include "CSVLogger.hpp"
#include <stdlib.h>

static const char * dataLog = "./project3.csv";
static const char * dataSchema = "numt, mode, chunksize";

struct s
{
	float value;
	int pad[NUMPAD];
} Array[4];

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
    unsigned int NUMPADDING = atoi(argv[2]);

#ifndef _OPENMP
    printf("OpenMP is not supported here -- sorry.\n" );
    return 1;
#endif

    omp_set_num_threads(NUMT);
    printf("Using %d threads.\t", NUMT);

	const int SomeBigNumber = 100000000;	// keep < 2B
    double time0 = omp_get_wtime();
    
	#pragma omp parallel for default(none)
	for( int i = 0; i < 4; i++ )
	{
		unsigned int seed = 0;		// automatically private
		for( unsigned int j = 0; j < SomeBigNumber; j++ )
		{
			Array[i].value = Array[i].value + (float)rand_r( &seed );
		}
	}
    
    double megaMultsSec = ((double)numMuled / (omp_get_wtime() - time0)) /  1000000.;

    printf ("-> MegaMults/sec: %f\t", megaMultsSec);
    printf ("-> Product: %e\n", prod);
    CSVLogger::WriteLog("%u, %u, %s, %f, %f", NUMT, CHUNKSIZE, MODE, megaMultsSec, prod);
    CSVLogger::CloseLogFile();
}


