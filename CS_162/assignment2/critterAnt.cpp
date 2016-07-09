#include "critterAnt.hpp"

int CritterAnt::GetDeathSteps() const
{
    return CRITTER_ANT_DEATH_STEPS;
}

int CritterAnt::GetBreedSteps() const
{
    return CRITTER_ANT_BREED_STEPS;
}

critterType CritterAnt::GetCritterType() const
{
    return critterType::CritterType__Ant;
}


CritterAnt::CritterAnt() : Critter()
{

}

CritterAnt::~CritterAnt()
{

}
