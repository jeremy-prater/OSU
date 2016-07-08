#include <stdlib.h>
#include <string.h>
#include "critter.hpp"
#include "critterAnt.hpp"
#include "critterDoodleBug.hpp"

const int gridX = 20;
const int gridY = 20;

Critter * gridMain[gridX][gridY];

int main()
{
    CritterAnt myAnt;
    CritterDoodleBug myBug;

    myAnt.move();
    myBug.move();
    return 0;
}
