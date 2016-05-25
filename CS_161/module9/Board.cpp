/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 24, 2016
** Description:  Module 9 assignment
*********************************************************************/
#include "Board.hpp"

#include <iostream>
#include <string.h>

/*********************************************************************
** Description: Assignment 9
**
** Implementation for Board.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// Board constructors
//

/////////////////////////////////////////////////////////////////
//
// Board::Board()
//
// Class constructor with default variables
//

Board::Board (currentPlayerTurn startingPlayer);
{
  memset (0, this->board, sizeof (board));
  currentGameState = UNFINISHED;
  currentPlayerTurn = startingPlayer;
}

/////////////////////////////////////////////////////////////////
//
// bool makeMove(int x, int y)
//
// Input a new move to the board and update the tic-tac-toe array
//
// Return : True if a valid move is Input.
//          False is that spot is already taken by a piece.
//

bool Board::makeMove (int x, int y)
{
  // Check if x,y is a valid move.
  if (board[x][y] != NO_PLAYER)
  {
    return false;
  }

  // Update board...
  board[x][y] = currentPlayerTurn;

  if (currentPlayerTurn == X_TURN)
  {
    currentPlayerTurn = O_TURN;
  }
  else
  {
    currentPlayerTurn = X_TURN;
  }

  // Update gameState if required.
}

/////////////////////////////////////////////////////////////////
//
// gameState_e Board::gameState()
//
// Return : The current game state.
//

gameState_e Board::gameState()
{
  return currentGameState;
}

/////////////////////////////////////////////////////////////////
//
// playerTurn_e Board::gamePlayer()
//
// Return : The current players turn.
//

playerTurn_e Board::gamePlayer()
{
  return currentPlayerTurn;
}

/////////////////////////////////////////////////////////////////
//
// void Board::printBoard();
//
// Print the current board configuration to the console.
//

gameState_e Board::printBoard()
{
  std::cout << std::endl << std::endl;
  std::cout << "   0   1   2 \n";
  std::cout << "0  " << getPieceHelper(0,0) << " | "<< getPieceHelper(1,0) <<" | " << getPieceHelper(2,0) << "\n";
  std::cout << "  -----------\n";
  std::cout << "1  " << getPieceHelper(0,1) << " | "<< getPieceHelper(1,1) <<" | " << getPieceHelper(2,1) << "\n";
  std::cout << "  -----------\n";
  std::cout << "2  " << getPieceHelper(0,2) << " | "<< getPieceHelper(1,2) <<" | " << getPieceHelper(2,2) << "\n";
}

/////////////////////////////////////////////////////////////////
//
// char Board::getPieceHelper(int x, int y)
//
// Helper function to return the character equivalent of a piece enum.
//

char Board::getPieceHelper(int x, int y)
{
  if (board[x][y] == X_TURN)
  {
    return 'X';
  }
  if (board[x][y] == O_TURN)
  {
    return 'O';
  }
  return '.';
}
