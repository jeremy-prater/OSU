#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

class gamePlayer
{
private:
    gameSpace * currentSpace;
    gameObject backpackItems[5];

    // This is a 1:1 mapping to gameSpaceDescription::connectedSpaces
    gameSpaceLocation possibleSpaces[4];

public:
    bool CanMoveToSpace (gameSpaceLocation testLocation);
    void MoveToSpace (gameSpaceLocation moveLocation);

    bool CanTakeItem(gameObject * object);
    void TakeItem(gameObject * object);

    bool CanUseItem(gameObject * object);
    void UseItem(gameObject * object);    
};

#endif // GAME_PLAYER_HPP