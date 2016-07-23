#ifndef DICE_COMBO_HPP
#define DICE_COMBO_HPP

#include "dice.hpp"
#include <vector>

class DiceCombo
{
private:
  unsigned int NumDice;
  std::vector<Dice> dice;

public:
  DiceCombo(unsigned int numDice, unsigned int numSides);

  DiceCombo() { }
  ~DiceCombo() { }

  virtual unsigned int RollAllDice();
};

#endif // DICE_COMBO_HPP
