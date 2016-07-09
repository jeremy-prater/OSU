#include "critterDoodleBug.hpp"

int CritterDoodleBug::GetDeathSteps() const
{
    return CRITTER_DOODLEBUG_DEATH_STEPS;
}

int CritterDoodleBug::GetBreedSteps() const
{
    return CRITTER_DOODLEBUG_BREED_STEPS;
}

critterType CritterDoodleBug::GetCritterType() const
{
    return critterType::CritterType__DoodleBug;
}


CritterDoodleBug::CritterDoodleBug() : Critter()
{

}

CritterDoodleBug::~CritterDoodleBug()
{

}
