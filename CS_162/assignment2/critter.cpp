#include "critter.hpp"
#include <stdio.h>

int Critter::GetDeathSteps() const
{
    return 0;
}

int Critter::GetBreedSteps() const
{
    return 0;
}

void Critter::move()
{
    printf ("deathSteps: %d\n", this->GetDeathSteps());
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
