#include "gameSpaceController.hpp"
#include "lib_flip_display.hpp"

gameSpaceController::gameSpaceController()
{
    int currentSpaceIndex = 0;
    DebugConsole::debug_print(1, true, COLOR_CYAN, "Creating gameSpaces\n");
    while (gameSpace::gameSpaceDescriptions[currentSpaceIndex].thisSpace != gameSpaceLocationInvalid)
    {
        gameSpaces.push_back (new gameSpace (&gameSpace::gameSpaceDescriptions[currentSpaceIndex]));
        currentSpaceIndex++;
    }
    DebugConsole::debug_print(1, true, COLOR_CYAN, "Parsed %d gameSpaceDescriptions\n", currentSpaceIndex);    
}

gameSpaceController::~gameSpaceController()
{

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