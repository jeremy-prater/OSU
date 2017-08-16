#ifdef TSP_TOUR_GA_H
#define TSP_TOUR_GA_H

#include "tourPop.h"

class TourGA
{
public:
    static TourPop * evolvePopulation(TourPop * pop);
    static Tour * crossover (Tour * parent1, Tour * parent2);
    static void mutate(Tour * tour);
    static Tour * tournamentSelection(TourPop * pop);


private:
    static double mutationRate;
    static int tournamentSize;
    static bool elitism;
}

#endif // TSP_TOUR_GA_H