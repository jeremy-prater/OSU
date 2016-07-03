#ifndef DICE_H
#define DICE_H

class Dice
{
private:
  unsigned int numFaces;
public:
  unsigned int GetNumFaces();
  virtual unsigned int Roll();

  Dice();
  Dice (unsigned int newNumFaces);
}

class LoadedDice : Dice
{
  unsigned int Roll();
}

#endif // DICE_H
