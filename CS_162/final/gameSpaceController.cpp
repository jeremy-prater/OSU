#include "gameSpaceController.hpp"
#include "gameSpaces.hpp"
#include "lib_flip_display.hpp"

gameSpaceController::gameSpaceController()
{
    int currentSpaceIndex = 0;
    DebugConsole::debug_print(1, true, COLOR_CYAN, "Creating gameSpaces\n");
    while (gameSpace::gameSpaceDescriptions[currentSpaceIndex].thisSpace != gameSpaceLocationInvalid)
    {
        switch (gameSpace::gameSpaceDescriptions[currentSpaceIndex].thisSpace)
        {
            case gameSpaceLocationForest:
            {
                gameSpaces.push_back (new gameSpaceForest (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationTrail1:
            {
                gameSpaces.push_back (new gameSpaceTrail1 (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationRiver:
            {
                gameSpaces.push_back (new gameSpaceRiver (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationTrail2:
            {
                gameSpaces.push_back (new gameSpaceTrail2 (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationCabin:
            {
                gameSpaces.push_back (new gameSpaceCabin (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationCabinBasement:
            {
                gameSpaces.push_back (new gameSpaceCabinBasement (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationTrail3:
            {
                gameSpaces.push_back (new gameSpaceTrail3 (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationCave:
            {
                gameSpaces.push_back (new gameSpaceCave (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationCaveRoom:
            {
                gameSpaces.push_back (new gameSpaceCaveRoom (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationTrail4:
            {
                gameSpaces.push_back (new gameSpaceTrail4 (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationPond:            
            {
                gameSpaces.push_back (new gameSpacePond (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            default:
            {
                DebugConsole::debug_print(1, true, COLOR_YELLOW, "Attempted to create unknown gameSpace (%d).\n", gameSpace::gameSpaceDescriptions[currentSpaceIndex].thisSpace);
            }
            break;
        }
        currentSpaceIndex++;
    }
    DebugConsole::debug_print(1, true, COLOR_CYAN, "Parsed %d gameSpaceDescriptions\n", currentSpaceIndex);    
}

gameSpaceController::~gameSpaceController()
{
    int currentSpaceIndex = 0;
    DebugConsole::debug_print(1, true, COLOR_CYAN, "Destroying gameSpaces\n");
    while (currentSpaceIndex < gameSpaces.size())
    {
        delete gameSpaces[currentSpaceIndex++];
    }    
}

gameSpace * gameSpaceController::GetGameSpaceByType(gameSpaceLocation location)
{
    int index = 0;
    while (index < gameSpaces.size())
    {
        if (gameSpaces[index]->GetSpaceDescription().thisSpace == location)
        return gameSpaces[index];
        index++;
    }
    DebugConsole::debug_print(1, true, COLOR_RED, "Unable to locate space (%d). Returning null. Program may crash!\n", location);
    return __null;
}

gameSpace * gameSpaceController::GetCurrentSpace()
{
    return currentSpace;
}
void  gameSpaceController::SetCurrentSpace(gameSpace * space)
{
    currentSpace = space;
}