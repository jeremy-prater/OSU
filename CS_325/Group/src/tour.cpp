#include "Tour.h"
#include <algorithm>
#include <random>
#include <iterator>

auto Tour::randomShuffle = std::default_random_engine {};

Tour::Tour (TourSet * parentSet)
{
    tourSet = parentSet;
    fitness = 0;
    distance = 0;
}

void Tour::generate()
{
    std::vector<City *> * cityList = TourSet::getCityList();
    std::copy(cityList->begin(), cityList->end(), back_inserter(tour));
    std::shuffle(tour.begin(), tour.end(), randomShuffle);
}

City * Tour::getCity (int position)
{
    return tour[position];
}

void Tour::setCity (int position, City * city)
{
    tour[position] = city;
    fitness = 0;
    distance = 0;
}

double Tour::getFitness()
{
    if (fitness == 0)
    {
        fitness = 1 / (double)getDistance();
    }
    return fitness;
}
int Tour::getDistance()
{
    if (distance == 0)
    {
        int tourDistance = 0;
        for (int cityIndex = 0; cityIndex < tour.size(), cityIndex++)
        {
            City * startCity = getCity(cityIndex);
            City * endCity;
            if (cityIndex + 1 < tour.size())
            {
                endCity = getCity (cityIndex + 1);
            }
            else
            {
                endCity = getCity (0);
            }
            tourDistance += startCity->getDistance(endCity);
        }
        distance = tourDistance;
    }
    return distance;
}
int Tour::tourLength()
{
    return tour.size();
}

bool Tour::containsCity(City * city)
{
    if (std::find(tour.begin(), tour.end(), city) != tour.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}
