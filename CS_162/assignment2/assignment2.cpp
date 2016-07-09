#include <stdlib.h>
#include <string.h>
#include "critter.hpp"
#include "critterAnt.hpp"
#include "critterDoodleBug.hpp"
#include "lib_flip_display.hpp"

const int gridX = 20;
const int gridY = 20;

Critter * gridMain[gridX][gridY];

void PrintGrid()
{
    screen_clear();
    cursor_move_to(0,0);

    debug_print(true, COLOR_GREEN, "\nDoodleBugs and Ants V1.0\n\n");

    debug_print(false, COLOR_WHITE, "Round : %d\n\n", 12);

    debug_print(true, COLOR_WHITE,"  |01234567890123456789|\n");
    debug_print(true, COLOR_WHITE, "--|--------------------|--\n");
    for(int dY=0;dY<gridY;dY++)
    {
        debug_print(true, COLOR_WHITE, "%02d|",dY);
        for (int dX = 0;dX < gridX;dX++)
        {
            if (gridMain[dX][dY] != 0)
            {
                switch (gridMain[dX][dY]->GetCritterType())
                {
                    case critterType::CritterType__None:
                        debug_print(false, COLOR_WHITE, " ");
                    break;

                    case critterType::CritterType__DoodleBug:
                        debug_print(true, COLOR_CYAN, "*");
                    break;

                    case critterType::CritterType__Ant:
                    default:
                        debug_print(true, COLOR_RED, ".");
                    break;
                }
            }
            else
            {
                debug_print(false, COLOR_WHITE, " ");
            }
        }
        debug_print(true, COLOR_WHITE, "|\n");
    }
    debug_print(true, COLOR_WHITE, "--|--------------------|--\n");
    debug_print(true, COLOR_WHITE, "  |                    |\n");

    debug_print(true, COLOR_WHITE,"\nControls\n\n");
    debug_print(false, COLOR_WHITE,"(space) - Next Round\n");
    debug_print(false, COLOR_WHITE,"(d)     - Print Debug Data\n");
    debug_print(false, COLOR_WHITE,"(g)     - Set the program to automatic. Use any key to break automatic mode.\n");    
    debug_print(false, COLOR_WHITE,"(q)     - Terminate Program");

}

void gridTurn()
{
    for (int dX = 0;dX < gridX;dX++)
    {
        for(int dY=0;dY<gridY;dY++)
        {
            if (gridMain[dX][dY] != 0)
            {
                switch (gridMain[dX][dY]->move())
                {
                    case critterMovement::CRITTER_UP:
                    {
                        // Moving Critter UP (-dY)
                        if (dY > 0)
                        {
                            if (gridMain[dX][dY-1] != 0)
                            {
                                // Someone is in this spot!!
                            }
                        }
                    }
                    break;
                    case critterMovement::CRITTER_DOWN:
                    {
                        // Moving Critter DOWN (+dY)
                        if ((dY+1) < gridY)
                        {
                            if (gridMain[dX][dY+1] != 0)
                            {
                                // Someone is in this spot!!
                            }
                        }
                    }
                    break;
                    case critterMovement::CRITTER_LEFT:
                    {
                        // Moving Critter LEFT (-dX)
                        if (dX > 0)
                        {
                            if (gridMain[dX-1][dY] != 0)
                            {
                                // Someone is in this spot!!
                            }
                        }

                    }
                    break;
                    case critterMovement::CRITTER_RIGHT:
                    {
                        // Moving Critter RIGHT (+dX)
                        if ((dX+1) < gridX)
                        {
                            if (gridMain[dX+1][dY] != 0)
                            {
                                // Someone is in this spot!!
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
}

int main()
{
    gridMain[2][2] = gridMain[4][2] = new CritterAnt();
    gridMain[3][9] = new CritterDoodleBug();

    PrintGrid();
    return 0;
}
