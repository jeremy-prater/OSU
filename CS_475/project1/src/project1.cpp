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
#include "curveCalc.h"
#include "project1.h"

#include <pthread.h>

static const char * dataLog = "./project1.csv";
static const char * dataSchema = "NUMT, NUMNODES, ";

int main( int argc, char *argv[ ] )
{
    if (argc != 3)
    {
        printf("Incorrect number of arguments...\n");
        exit(-1);
    }

    unsigned int NUMT = atoi (argv[1]);
    unsigned int NUMNODES = atoi (argv[2]);

#ifndef _OPENMP
    printf("OpenMP is not supported here -- sorry.\n" );
    return 1;
#endif

    omp_set_num_threads(NUMT);
    printf("Using %d threads * %d nodes \t", NUMT, NUMNODES);

	// the area of a single full-sized tile:
	float fullTileArea = (  ( (XMAX-XMIN)/(float)(NUMNODES-1) )  *  ( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );

	// sum up the weighted heights into the variable "volume"
    float volume = 0;
    double time0 = omp_get_wtime( );
	// using an OpenMP for loop and a reduction:

    #pragma omp parallel for default(none), shared(fullTileArea), shared(NUMNODES), reduction(+:volume)
    for( int i = 0; i < NUMNODES*NUMNODES; i++ )
    {
        
        int iu = i % NUMNODES;
        int iv = i / NUMNODES;

        float height = Height (iu, iv, NUMNODES);
        // Find the location (center, edge, corner) of the current node and weight the result.
        float weighting = 1.;
        if ((iu == 0) || (iu == (NUMNODES - 1)))
        {
            weighting /= 2; // Could be an edge or corner
        }
        if ((iv == 0) || (iv == (NUMNODES - 1)))
        {
            weighting /= 2; // Could be an edge or corner
        }
        volume += height * weighting * fullTileArea;
    }
    
    double time1 = omp_get_wtime( );
    double megaHeights = (double)(NUMNODES*NUMNODES)/(time1-time0)/1000000.;

    printf ("-> tile size: %f ", fullTileArea);
    printf ("-> total volume: %f ", volume);
    printf ("-> megaHeights/sec: %f\n", megaHeights);
}


