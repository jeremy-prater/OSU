#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "classDecl.hpp"
#include "gameSpace.hpp"
#include "gameObject.hpp"

class gameState
{
private:
    gameSpaceController * Controller;
    gamePlayer * Player;
    int MovesLeft;

public:
    std::string PrintRound();
    void InteractObject (gameObject * object);
    void GameLoop();

    gameState();
    ~gameState();
};

#endif // GAME_STATE_HPP