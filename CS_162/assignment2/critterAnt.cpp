#include "critterAnt.hpp"
#include "lib_flip_display.hpp"

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
    SetDeathTurns (CRITTER_ANT_DEATH_STEPS);
    SetBreedTurns (CRITTER_ANT_BREED_STEPS);
}

CritterAnt::~CritterAnt()
{

}
