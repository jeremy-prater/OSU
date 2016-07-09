#include "critter.hpp"
#include <stdio.h>
#include <stdlib.h>

int Critter::GetDeathSteps() const
{
    return 0;
}

int Critter::GetBreedSteps() const
{
    return 0;
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

}

void Critter::breed()
{

}

void Critter::die()
{

}

Critter::Critter()
{

}

Critter::~Critter()
{

}
