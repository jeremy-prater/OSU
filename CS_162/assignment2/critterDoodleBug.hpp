#ifndef CRITTER_DOODLEBUG_H
#define CRITTER_DOODLEBUG_H

#include "critter.hpp"

class CritterDoodleBug : public Critter
{
public:
    int GetDeathSteps() const;
    int GetBreedSteps() const;

    CritterDoodleBug();
    ~CritterDoodleBug();
};

#endif // CRITTER_DOODLEBUG_H
