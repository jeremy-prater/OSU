#ifndef TSP_TOUR_MANAGER_H
#define TSP_TOUR_MANAGER_H

#include <vector>
#include "city.h"
#include "tourSet.h"

class Tour
{
public:
    Tour ();
    void generate();
    City * getCity (int position);
    void setCity (int position, City * city);
    double getFitness();
    int getDistance();
    int tourLength();
    bool containsCity(City * city);

private:
    std::vector<City *> tour;
    int distance;
    double fitness;

    static auto randomShuffle;
};

#endif // TSP_TOUR_MANAGER_H