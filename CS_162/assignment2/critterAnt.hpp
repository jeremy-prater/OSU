#ifndef CRITTER_ANT_H
#define CRITTER_ANT_H

#include "critter.hpp"

class CritterAnt : public Critter
{
public:
    int GetDeathSteps() const;
    int GetBreedSteps() const;
    critterType GetCritterType() const;
    void eat();

    CritterAnt();
    ~CritterAnt();
};

#endif // CRITTER_ANT_H
