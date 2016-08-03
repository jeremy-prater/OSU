#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include "gameObjects.hpp"
#include "gameSpace.hpp"
#include "gameSpaceController.hpp"

class gamePlayer
{
private:
    gameSpace * currentSpace;
    gameObject * backpackItems[5];

    // This is a 1:1 mapping to gameSpaceDescription::connectedSpaces
    gameSpaceLocation possibleSpaces[4];
    gameSpaceController * gameSpaceControllerInstance;

public:
    gamePlayer (gameSpaceController * instance);
    ~gamePlayer();

    bool CanMoveToSpace (gameSpaceLocation testLocation);
    void MoveToSpace (gameSpaceLocation moveLocation);

    bool CanTakeItem(gameObject * object);
    void TakeItem(gameObject * object);

    bool CanUseItem(gameObject * object);
    void UseItem(gameObject * object);    
};

#endif // GAME_PLAYER_HPP