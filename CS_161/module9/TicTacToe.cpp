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
  int playX, playY;
  playX = playY = 0;
  while (gameBoard->gameState() == UNFINISHED)
  {
    std::cout << "\n\n -- Round : " << round++ << std::endl;
    std::cout << " -- Player : ";

    if (gameBoard->gamePlayer() == X_TURN)
    {
      std::cout << "X";
    }
    else if (gameBoard->gamePlayer() == O_TURN)
    {
      std::cout << "O";
    }
    std::cout << std::endl << std::endl << std::endl;

    gameBoard->printBoard();

    std::cout << "Enter coordinates to play :";
    std::cin >> playX >> playY;

    if (gameBoard->makeMove (playX, playY) == false)
    {
      std::cout << " -- Invalid move!! " << playX << ", " << playY << " is already taken!!" << std::endl << std::endl;
    }
  }
}

void main()
{
  TicTacToe test ('x');
  test.play();
  return 0;
}
