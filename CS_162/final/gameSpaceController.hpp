#ifndef GAME_SPACE_CONTROLLER_HPP
#define GAME_SPACE_CONTROLLER_HPP

#include "gameSpace.hpp"

class gameSpaceController
{
private:
    std::vector<gameSpace *> gameSpaces;
    gameSpace * currentSpace;
    gamePlayer * Player;

public:
    gameSpaceController();
    ~gameSpaceController();
    
    gameSpace * GetGameSpaceByType(gameSpaceLocation location);
    void SetPlayer (gamePlayer * plaer);
    gamePlayer * GetPlayer();
    void SetCurrentSpace (gameSpace * space);
    gameSpace * GetCurrentSpace();
};

#endif // GAME_SPACE_CONTROLLER_HPP