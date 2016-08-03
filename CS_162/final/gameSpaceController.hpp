#ifndef GAME_SPACE_CONTROLLER_HPP
#define GAME_SPACE_CONTROLLER_HPP

#include "gameSpace.hpp"

class gameSpaceController
{
private:
    std::vector<gameSpace *> gameSpaces;
    gameSpace * currentSpace;

public:
    gameSpaceController();
    ~gameSpaceController();
    
    gameSpace * GetGameSpaceByType(gameSpaceLocation location);
  
};

#endif // GAME_SPACE_CONTROLLER_HPP