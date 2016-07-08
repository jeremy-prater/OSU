#include "critter.hpp"

int Ant::GetDeathSteps()
{
    return ANT_DEATH_STEPS;
}

int Ant::GetBreedSteps()
{
    return ANT_BREED_STEPS;
}

Ant::Ant() : Critter()
{

}

Ant::~Ant()
{

}
