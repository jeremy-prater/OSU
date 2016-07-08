#include "critterDoodlebug.hpp"

int CritterDoodleBug::GetDeathSteps() const
{
    return CRITTER_DOODLEBUG_DEATH_STEPS;
}

int CritterDoodleBug::GetBreedSteps() const
{
    return CRITTER_DOODLEBUG_BREED_STEPS;
}

CritterDoodleBug::CritterDoodleBug() : Critter()
{

}

CritterDoodleBug::~CritterDoodleBug()
{

}
