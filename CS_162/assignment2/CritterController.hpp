#ifndef ASSIGNMENT_2_HPP
#define ASSIGNMENT_2_HPP

#include "critter.hpp"

#define DEFAULT_NUM_ANTS 100
#define DEFAULT_NUM_DOODLEBUGS 20

class CritterController
{
private:
    static const int gridX = 20;
    static const int gridY = 20;

    Critter * gridMain[gridX][gridY];
    int turnCounter;

    int DoodlebugDeathTurns;
    int DoodlebugBreedTurns;
    int AntDeathTurns;
    int AntBreedTurns;
    
public:
    CritterController();
    ~CritterController();

    void Randomize ();

    void PrintGrid();
    void GridTurn();

    void SetupLimits (int newDoodleBugBreedTurns, int newDoodleBugDeathTurns, int newAntBreedTurns, int newAntDeathTurns);
    void SetupGrid (int numDoodleBugs, int numAnts);
    void DestroyGrid();
};

#endif // ASSIGNMENT_2_HPP
