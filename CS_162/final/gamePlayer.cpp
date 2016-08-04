#include "gamePlayer.hpp"
#include "gameSpaceController.hpp"
#include "lib_flip_display.hpp"

gamePlayer::gamePlayer(gameSpaceController * instance)
{
    gameSpaceControllerInstance = instance;
}

gamePlayer::~gamePlayer()
{

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
    DebugConsole::debug_print (1, true, COLOR_YELLOW, "[%s] PLayer moved to space %s (0x%p)!\n", __func__, currentSpace->GetSpaceDescription().spaceName.c_str(), currentSpace);    
    return true;
}