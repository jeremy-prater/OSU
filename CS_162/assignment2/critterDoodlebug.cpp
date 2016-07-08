#include "critter.hpp"

int DoodleBug::GetDeathSteps()
{
    return DOODLEBUG_DEATH_STEPS;
}

int DoodleBug::GetBreedSteps()
{
    return DOODLEBUG_BREED_STEPS;
}

DoodleBug::DoodleBug() : Critter()
{

}

DoodleBug::~DoodleBug()
{

}
