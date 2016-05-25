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
  if (board == nullptr)
  {
    return;
  }

  int round = 0;
  int playX, playY;
  playX = playY = 0;
  while (board->gameState() == UNFINISHED)
  {
    cout << "\n\n -- Round : " << round++ << std::endl;
    cout << " -- Player : ";

    if (board->gamePlayer() == X_TURN)
    {
      cout << "X";
    }
    else if (board->gamePlayer() == O_TURN)
    {
      cout << "O";
    }
    cout << std::endl << std::endl << std::endl;

    board->printBoard();

    cout << "Enter coordinates to play :";
    cin >> playX >> playY;

    if (board->makeMove (playX, playY) == false)
    {
      cout << " -- Invalid move!! " << playX << ", " << playY << " is already taken!!" << std::endl << std::endl;
    }
  }
}

void main()
{
  TicTacToe test ('x');
  test.play();
}
