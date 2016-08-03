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
        DebugConsole::debug_print (1, true, COLOR_RED, "%s Defaulting to false due to bad location (%d)\n", __func__, location);
        return false;
    }
    return gameSpaceObject->CanMoveTo(this);
}