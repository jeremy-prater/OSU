#ifndef CHARACTER_BASE_HPP
#define CHARACTER_BASE_HPP

#include "diceCombo.hpp"

enum CharacterTypes
{
  CharacterTypeInvalid = -1,
  CharacterTypeMedusa,
  CharacterTypeGollum,
  CharacterTypeReptilePeople,
  CharacterTypeBlueMen,
  CharacterTypeHarryPotter,
  CharacterTypeNumCharacters
};

class CharacterBase
{
protected:
  DiceCombo AttackPower;
  DiceCombo DefensePower;
  unsigned int Armor;
  unsigned int Strength;

public:
  CharacterBase() { }
  ~CharacterBase() { }

  virtual void SetupAttackDice() = 0;
  virtual void SetupDefenseDice() = 0;
  virtual void SetupArmor() = 0;
  virtual void SetupStrength() = 0;
  virtual const char * GetName() = 0;
  virtual unsigned int GenerateAttack ();
  virtual unsigned int GenerateDefense();
  virtual void DefendAttack(unsigned int damage);
  unsigned int GetStrength();
};

#endif // CHARACTER_BASE_HPP