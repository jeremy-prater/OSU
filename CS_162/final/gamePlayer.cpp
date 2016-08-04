#include <string.h>
#include "gamePlayer.hpp"
#include "gameSpaceController.hpp"
#include "lib_flip_display.hpp"

gamePlayer::gamePlayer(gameSpaceController * instance)
{
    gameSpaceControllerInstance = instance;
    memset (backpackItems, 0, sizeof (backpackItems));
}

gamePlayer::~gamePlayer()
{
    // Delete any backpack items...
    for (int itemIndex = 0; itemIndex < NUM_ITEMS_INVENTORY; itemIndex++)
    {
        if (backpackItems[itemIndex] != __null)
        {
            delete backpackItems[itemIndex];
            backpackItems[itemIndex] = __null;
        }
    }
}

bool gamePlayer::CanMoveToSpace (gameSpaceLocation location)
{
    gameSpace * gameSpaceObject = gameSpaceControllerInstance->GetGameSpaceByType(location);
    if (gameSpaceObject == __null)
    {
        DebugConsole::debug_print (1, true, COLOR_RED, "[%s] Defaulting to false due to bad location (%d)\n", __func__, location);
        return false;
    }
    return gameSpaceObject->CanMoveTo(this);
}


bool gamePlayer::MoveToSpace (gameSpaceLocation location)
{
    if (!CanMoveToSpace(location))
    {
        DebugConsole::debug_print (1, true, COLOR_YELLOW, "[%s] Attempted to move player to (%d) is not allowed by location!\n", __func__, location);
        return false;
    }  
    currentSpace = gameSpaceControllerInstance->GetGameSpaceByType(location);
    DebugConsole::debug_print (1, true, COLOR_YELLOW, "[%s] Player moved to space %s (0x%p)!\n", __func__, currentSpace->GetSpaceDescription().spaceName.c_str(), currentSpace);
    gameSpaceControllerInstance->SetCurrentSpace (currentSpace);    
    return true;
}

gameObject ** gamePlayer::GetBackpack()
{
    return backpackItems;
}

gameSpace * gamePlayer::GetCurrentSpace()
{
    return currentSpace;
}