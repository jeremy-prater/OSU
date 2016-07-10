#include "critter.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "lib_flip_display.hpp"

int Critter::GetDeathSteps() const
{
    return deathTurns;
}

int Critter::GetBreedSteps() const
{
    return breedTurns;
}

void Critter::SetBreedTurns (int newBreedTurns)
{
    breedTurns = newBreedTurns;
}

void Critter::SetDeathTurns (int newDeathTurns)
{
    deathTurns = newDeathTurns;
}

critterType Critter::GetCritterType() const
{
    return critterType::CritterType__None;
}

critterMovement Critter::move()
{
    return (critterMovement)(rand() % (int)critterMovement::CRITTER_NUM_MOVES);
}

void Critter::eat()
{
    stepCounter++;
}

bool Critter::breed()
{
    if ((stepCounter - lastBreed) >= GetBreedSteps())
    {
        lastBreed = stepCounter;
        return true;
    }
    return false;
}

bool Critter::died()
{
    return ((stepCounter - lastEat) >= GetDeathSteps());
}

bool Critter::GetHasMoved() const
{
    return hasMoved;
}

void Critter::SetHasMoved(bool moved)
{
    hasMoved = moved;
}

Critter::Critter()
{
    stepCounter = 0;
    lastBreed = 0;
    lastEat = 0;
    hasMoved = false;
}

Critter::~Critter()
{

}
