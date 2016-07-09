#ifndef CRITTER_DOODLEBUG_H
#define CRITTER_DOODLEBUG_H

#include "critter.hpp"

class CritterDoodleBug : public Critter
{
private:
    bool eatingAnt;

public:
    int GetDeathSteps() const;
    int GetBreedSteps() const;
    critterType GetCritterType() const;
    void EatAnt();
    void eat();

    CritterDoodleBug();
    ~CritterDoodleBug();
};

#endif // CRITTER_DOODLEBUG_H
