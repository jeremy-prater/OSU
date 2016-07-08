#include <stdlib.h>
#include <string.h>
#include "critter.hpp"

const int gridX = 20;
const int gridY = 20;

Critter gridMain[gridX][gridY];

Ant * myAnt2;

int main()
{
    Critter * myCritter;
    myCritter = &gridMain[1][1];
    myCritter->move();

    Ant * myAnt;

    myAnt = (Ant*)gridMain[1][1];
    myAnt->move();

    /*DoodleBug * currentBug;
    currentBug = (DoodleBug*)&gridMain[1][1];
    currentBug->move();*/

    return 0;
}
