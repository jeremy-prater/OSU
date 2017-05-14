////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 4 - Control Threads
//
// Jeremy Prater
//
// Main Header
//

#ifndef PROJECT4_MAIN_H
#define PROJECT4_MAIN_H

typedef struct
{
    int	    NowYear;		// 2017 - 2022
    int	    NowMonth;		// 0 - 11

    float	NowPrecip;		// inches of rain per month
    float	NowTemp;		// temperature this month
    float	NowHeight;		// grain height in inches
    int	    NowNumDeer;		// number of deer in the current population
} SystemState;

#endif // PROJECT4_MAIN_H