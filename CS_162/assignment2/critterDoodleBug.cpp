#include "critterDoodleBug.hpp"
#include "lib_flip_display.hpp"

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

void CritterDoodleBug::eat()
{
    stepCounter++;
    if (eatingAnt)
    {
        eatingAnt = false;
        lastEat = stepCounter;
        debug_print (true, COLOR_CYAN, "%x was fed. Timer reset\n", this);
    }
    //debug_print (false, COLOR_WHITE, "DoodleBugs %x eating @ %d\n", this, stepCounter);
}

void CritterDoodleBug::EatAnt()
{
    eatingAnt = true;
}

CritterDoodleBug::CritterDoodleBug() : Critter()
{
    eatingAnt = false;
}

CritterDoodleBug::~CritterDoodleBug()
{

}