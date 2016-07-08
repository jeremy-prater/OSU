#ifndef CRITTER_H
#define CRITTER_H

#define ANT_BREED_STEPS 8
#define ANT_DEATH_STEPS 10
#define DOODLEBUG_DEATH_STEPS 3
#define DOODLEBUG_BREED_STEPS 3

enum critterType
{
    noCritter = 0,
    DoodleBug = 1,
    Ant       = 2
};

enum critterMovement
{
    CRITTER_UP,
    CRITTER_DOWN,
    CRITTER_LEFT,
    CRITTER_RIGHT,
    CRITTER_NUM_MOVES
};

class Critter
{
private:
    critterType type;
    int stepCounter;
    int lastBreed;
    int lastEat;

public:
    Critter();
    ~Critter();

    virtual int GetDeathSteps();
    virtual int GetBreedSteps();

    void move();
    void eat();
    void breed();
    void die();
};

class Ant : public Critter
{
public:
    int GetDeathSteps();
    int GetBreedSteps();

    Ant();
    ~Ant();
};

class DoodleBug : public Critter
{
public:
    int GetDeathSteps();
    int GetBreedSteps();

    DoodleBug();
    ~DoodleBug();
};

#endif // CRITTER_H
