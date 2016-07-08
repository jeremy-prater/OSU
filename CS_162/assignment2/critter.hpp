#ifndef CRITTER_H
#define CRITTER_H

#define CRITTER_ANT_BREED_STEPS 8
#define CRITTER_ANT_DEATH_STEPS 10
#define CRITTER_DOODLEBUG_DEATH_STEPS 3
#define CRITTER_DOODLEBUG_BREED_STEPS 3

enum class critterType
{
    noCritter,
    CritterDoodleBug,
    CritterAnt
};

enum class critterMovement
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
    //critterType type;
    int stepCounter;
    int lastBreed;
    int lastEat;

public:
    virtual int GetDeathSteps() const;
    virtual int GetBreedSteps() const;

    void move();
    void eat();
    void breed();
    void die();

    Critter();
    ~Critter();
};

#endif // CRITTER_H
