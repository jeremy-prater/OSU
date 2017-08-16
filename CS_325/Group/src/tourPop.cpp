#include "tourPop.h"

TourPopulation::TourPopulation(int populationSize, bool init)
{
    for (int index=0; index < populationSize; index++)
    {
        tours.push_back(NULL);
        if (init)
        {
            Tour * newTour = new Tour();
            newTour->generate();
            saveTour(index, newTour);
        }
    }
}

void TourPopulation::saveTour(int index, Tour * tour)
{
    tour[index] = tour;
}

Tour * TourPopulation::getTour(int index)
{
    return tour[index];
}

Tour * TourPopulation::getFittest()
{
    Tour * fittest = tours[0];
    for (int index = 1; index < tours.size(); index++)
    {
        if (fittest->getFitness() <= getTour(index)->getFitness())
        {
            fittest = getTour(index);
        }
    }
}

int TourPopulation::populationSize()
{
    return tours.size();
}
