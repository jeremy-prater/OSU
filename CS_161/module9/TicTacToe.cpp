/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 24, 2016
** Description:  Module 9 assignment
*********************************************************************/
#include "Board.hpp"
#include "TicTacToe.hpp"

#include <iostream>
#include <string>

/*********************************************************************
** Description: Assignment 9
**
** Implementation for TicTacToe.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// TicTacToe constructors
//

/////////////////////////////////////////////////////////////////
//
// TicTacToe::TicTacToe()
//
// Class constructor with first player
//

TicTacToe::TicTacToe(char firstMove)
{
  if ((firstMove == 'x') || (firstMove == 'X'))
  {
    gameBoard = new Board (X_TURN);
  }
  else if ((firstMove == 'o') || (firstMove == 'O'))
  {
    gameBoard = new Board (O_TURN);
  }
  else
  {
    gameBoard = 0;
  }
}

/////////////////////////////////////////////////////////////////
//
// TicTacToe::~TicTacToe()
//
// Class destructor
//

TicTacToe::~TicTacToe()
{
  if (gameBoard != 0)
  {
    delete gameBoard;
  }
}

/////////////////////////////////////////////////////////////////
//
// void TicTacToe::play ()
//
// Main game loop
//

void TicTacToe::play()
{
  if (gameBoard == 0)
  {
    return;
  }

  int round = 0;
  bool inputGood = false;
  int playX, playY;
  playX = playY = 0;
  while (gameBoard->gameState() == UNFINISHED)
  {
    std::cout << "\n\n -- Round : " << round << std::endl;
    std::cout << " -- Player : ";

    if (gameBoard->gamePlayer() == X_TURN)
    {
      std::cout << "X";
    }
    else if (gameBoard->gamePlayer() == O_TURN)
    {
      std::cout << "O";
    }
    std::cout << std::endl << std::endl;

    gameBoard->printBoard();

    std::cout << "Enter coordinates to play :";
    inputGood = false;
    while (!inputGood)
    {
      std::cin >> playX >> playY;
      if (!std::cin.good())
      {
        std::cin.ignore (10);
        std::cin.clear();
      }
      else
      {
        inputGood = true;
      }
    }

    if (gameBoard->makeMove (playX, playY) == false)
    {
      std::cout << std::endl<< " -- Invalid move!! " << playX << ", " << playY << " is already taken!!" << std::endl;
    }
    else
    {
      round++;
    }
  }
  switch (gameBoard->gameState())
  {
    case X_WON:
    {
      std::cout << std::endl << std::endl << "X Won !!" < std::endl;
      break;
    }
    case O_WON:
    {
      std::cout << std::endl << std::endl << "O Won !!" < std::endl;
      break;
    }
    case DRAW:
    {
      std::cout << std::endl << std::endl << "Draw (cat game?)" < std::endl;
      break;
    }
  }
}

int main()
{
  TicTacToe test ('x');
  test.play();
  return 0;
}
