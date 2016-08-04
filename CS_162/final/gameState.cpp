#include "gameState.hpp"
#include "gameSpaceController.hpp"
#include "gamePlayer.hpp"

gameState::gameState()
{
    Controller = new gameSpaceController();
    Player = new gamePlayer(Controller);
    Player->MoveToSpace (gameSpaceLocationForest);    
}

gameState::~gameState()
{
    delete Controller;
    delete Player;
}