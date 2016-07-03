#ifndef DICE_H
#define DICE_H

class Dice
{
private:
  unsigned int numFaces;

  void Init (unsigned int numNewFaces);

public:
  unsigned int GetNumFaces() const;
  virtual unsigned int Roll() const;

  Dice();
  Dice (unsigned int newNumFaces);
};

class LoadedDice : public Dice
{
public:

  unsigned int Roll();
  LoadedDice();
  LoadedDice(unsigned int numNewFaces);
};


#endif // DICE_H
