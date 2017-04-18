////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 1 - Numeric Integration
//
// Jeremy Prater
//

#include <omp.h>
#include <stdio.h>
#include <math.h>
#include "curve_calc.h"
#include "project1.h"
#include <pthread.h>

static const char * dataLog = "./project1.csv";
static const char * dataSchema = "NUMT, NUMNODES, ";

int main( int argc, char *argv[ ] )
{
    
#ifndef _OPENMP
    printf("OpenMP is not supported here -- sorry.\n" );
    return 1;
#endif

    omp_set_num_threads(NUMT);
    printf("Using %d threads\n", NUMT);

	// the area of a single full-sized tile:
	float fullTileArea = (  ( (XMAX-XMIN)/(float)(NUMNODES-1) )  *  ( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );

	// sum up the weighted heights into the variable "volume"
    float volume = 0;
	// using an OpenMP for loop and a reduction:

    #pragma omp parallel for default(none), shared(fullTileArea), reduction(+:volume)
    for( int i = 0; i < NUMNODES*NUMNODES; i++ )
    {
        int iu = i % NUMNODES;
        int iv = i / NUMNODES;

        float height = Height (iu, iv);
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

    printf ("total volume: %f\n", volume);
}


