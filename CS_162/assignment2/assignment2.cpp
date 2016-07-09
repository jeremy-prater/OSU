#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "critter.hpp"
#include "critterAnt.hpp"
#include "critterDoodleBug.hpp"
#include "lib_flip_display.hpp"

const int gridX = 20;
const int gridY = 20;

Critter * gridMain[gridX][gridY];
int turnCounter = 0;

void PrintGrid()
{
    //screen_clear();
    //cursor_move_to(0,0);

    debug_print(true, COLOR_GREEN, "\nDoodleBugs and Ants V1.0\n\n");

    debug_print(false, COLOR_WHITE, "Round : %d\n\n", turnCounter);

    debug_print(true, COLOR_WHITE, "  |01234567890123456789|\n");
    debug_print(true, COLOR_WHITE, "--|--------------------|--\n");

    int dbugs = 0;
    int ants = 0;

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
                        dbugs++;
                    break;

                    case critterType::CritterType__Ant:
                    default:
                        debug_print(true, COLOR_RED, ".");
                        ants++;
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
    debug_print(true, COLOR_WHITE, "  |                    |\n\n");

    debug_print(true, COLOR_WHITE,"DoodleBugs: %d\t\tAnts:%d\n",dbugs, ants);

    debug_print(true, COLOR_WHITE,"\nControls\n\n");
    debug_print(false, COLOR_WHITE,"(space) - Next Round\n");
    debug_print(false, COLOR_WHITE,"(d)     - Print Debug Data\n");
    debug_print(false, COLOR_WHITE,"(g)     - Set the program to automatic. Use (space) to break automatic mode.\n");
    debug_print(false, COLOR_WHITE,"(q)     - Terminate Program\n\n");

}

void gridTurn()
{
    for (int dX = 0; dX < gridX;dX++)
    {
        for(int dY = 0; dY < gridY;dY++)
        {
            if ((gridMain[dX][dY] != 0) && (!gridMain[dX][dY]->GetHasMoved()))
            {
                bool validMove = false;
                int newX = dX;
                int newY = dY;
                critterMovement direction = gridMain[dX][dY]->move();

                switch (direction)
                {
                    case critterMovement::CRITTER_UP:
                    {
                        newY--;
                    }
                    break;
                    case critterMovement::CRITTER_DOWN:
                    {
                        newY++;
                    }
                    break;
                    case critterMovement::CRITTER_LEFT:
                    {
                        newX--;
                    }
                    break;
                    case critterMovement::CRITTER_RIGHT:
                    {
                        newX++;
                    }
                    break;
                }

                if ((newX >= 0) && (newX < gridX) && (newY >= 0) && (newY < gridY))
                {
                    validMove = true;
                    if (gridMain[newX][newY] != 0)
                    {
                        if ((gridMain[dX][dY]->GetCritterType() == critterType::CritterType__DoodleBug) && (gridMain[newX][newY]->GetCritterType() == critterType::CritterType__Ant))
                        {
                            // The DoodleBug will eat this ant...
                            debug_print (true, COLOR_YELLOW, "ant %x eaten...\n", gridMain[newX][newY]);
                            delete gridMain[newX][newY];
                            gridMain[newX][newY] = 0;
                            ((CritterDoodleBug*)gridMain[dX][dY])->EatAnt();
                        }
                        else
                        {
                            validMove = false;
                        }
                    }
                }

                gridMain[dX][dY]->eat();
                if (gridMain[dX][dY]->died())
                {
                    debug_print (true, COLOR_RED, "%x died...\n", gridMain[dX][dY]);
                    delete gridMain[dX][dY];
                    gridMain[dX][dY] = 0;
                }
                else if (validMove)
                {
                    gridMain[newX][newY] = gridMain[dX][dY];
                    gridMain[newX][newY]->SetHasMoved(true);
                    if (gridMain[dX][dY]->breed())
                    {
                        debug_print (true, COLOR_CYAN, "%x breeding...\n", gridMain[dX][dY]);

                        if (gridMain[dX][dY]->GetCritterType() == critterType::CritterType__Ant)
                        {
                            gridMain[dX][dY] = new CritterAnt();
                        }
                        else if (gridMain[dX][dY]->GetCritterType() == critterType::CritterType__DoodleBug)
                        {
                            gridMain[dX][dY] = new CritterDoodleBug();
                        }
                        else
                        {
                            gridMain[dX][dY] = 0;
                        }
                    }
                    else
                    {
                        gridMain[dX][dY] = 0;
                    }
                }
            }
        }
    }
    for (int dX = 0; dX < gridX;dX++)
    {
        for(int dY = 0; dY < gridY;dY++)
        {
            if (gridMain[dX][dY] != 0)
            {
                gridMain[dX][dY]->SetHasMoved(false);
            }
        }
    }
    turnCounter++;
}

void DestroyGrid()
{
    for (int dX = 0; dX < gridX;dX++)
    {
        for(int dY = 0; dY < gridY;dY++)
        {
            if (gridMain[dX][dY] != 0)
            {
                delete gridMain[dX][dY];
                gridMain[dX][dY] = 0;
            }
        }
    }

}

int main()
{
    for (int t=0;t<20;)
    {
        int x = rand() % gridX;
        int y = rand() % gridY;
        if (gridMain[x][y] == 0)
        {
            gridMain[x][y] = new CritterDoodleBug();
            t++;
        }
    }
    for (int t=0;t<100;)
    {
        int x = rand() % gridX;
        int y = rand() % gridY;
        if (gridMain[x][y] == 0)
        {
            gridMain[x][y] = new CritterAnt();
            t++;
        }
    }

    bool running = true;
    bool processEvent = false;
    bool autoRun = false;
    PrintGrid();
    while (running)
    {
        int key = -1;
        processEvent = false;
        while (!processEvent)
        {
            key = getkey();
            switch (key)
            {
                case 'q':
                case 'Q':
                running = false;
                processEvent = true;
                break;

                case 'g':
                case 'G':
                autoRun = true;
                key=-1;
                break;

                case ' ':
                gridTurn();
                processEvent = true;
                break;

                default:
                processEvent = false;
                break;
            }
            if (autoRun)
            {
                gridTurn();
                processEvent = true;
                if (key != -1)
                {
                    autoRun = false;
                }
            }
        }
        PrintGrid();
        usleep (100 * 1000);
    }

    DestroyGrid();
    return 0;
}
