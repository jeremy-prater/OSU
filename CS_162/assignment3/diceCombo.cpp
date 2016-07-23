#include "diceCombo.hpp"

DiceCombo::DiceCombo (unsigned int numDice, unsigned int numSides)
{
  NumDice = numDice;
  for (unsigned int currentDice = 0; currentDice < NumDice; currentDice++)
  {
    dice.push_back(Dice (numSides));
  }
}

unsigned int DiceCombo::RollAllDice()
{
  int totalRoll = 0;
  for (unsigned int currentDice = 0; currentDice < NumDice; currentDice++)
  {
    totalRoll += dice[currentDice].Roll();
  }
  return totalRoll;
}
