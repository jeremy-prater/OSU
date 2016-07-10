#ifndef CRITTER_ANT_H
#define CRITTER_ANT_H

#include "critter.hpp"

class CritterAnt : public Critter
{
public:
    critterType GetCritterType() const;
    void eat();

    CritterAnt();
    ~CritterAnt();
};

#endif // CRITTER_ANT_H
