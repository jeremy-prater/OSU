#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include "classDecl.hpp"
#include "gameSpace.hpp"

#define NUM_ITEMS_INVENTORY 5

class gamePlayer
{
private:
    gameSpace * currentSpace;
    gameObject * backpackItems[NUM_ITEMS_INVENTORY];

    // This is a 1:1 mapping to gameSpaceDescription::connectedSpaces
    gameSpaceLocation possibleSpaces[4];
    gameSpaceController * gameSpaceControllerInstance;

public:
    gamePlayer (gameSpaceController * instance);
    ~gamePlayer();

    gameObject ** GetBackpack();
    gameSpace * GetCurrentSpace();

    bool CanMoveToSpace (gameSpaceLocation testLocation);
    bool MoveToSpace (gameSpaceLocation moveLocation);

    bool CanTakeItem(gameObject * object);
    void TakeItem(gameObject * object);

    bool CanUseItem(gameObject * object);
    void UseItem(gameObject * object);    
};

#endif // GAME_PLAYER_HPP