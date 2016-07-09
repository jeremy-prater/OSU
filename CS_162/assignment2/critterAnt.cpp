#include "critterAnt.hpp"
#include "lib_flip_display.hpp"

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

void CritterAnt::eat()
{
    stepCounter++;
    //debug_print (false, COLOR_WHITE, "Ant %x eating @ %d\n", this, stepCounter);
}


CritterAnt::CritterAnt() : Critter()
{

}

CritterAnt::~CritterAnt()
{

}
