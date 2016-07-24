#ifndef CHARACTER_BLUEMEN_HPP
#define CHARACTER_BLUEMEN_HPP

#include "characterBase.hpp"

#define BLUEMEN_NUM_ATTACK_DICE    2
#define BLUEMEN_ATTACK_DICE_SIDES  10
#define BLUEMEN_NUM_DEFENSE_DICE   3
#define BLUEMEN_DEFENSE_DICE_SIDES 6

#define BLUEMEN_ARMOR              3
#define BLUEMEN_STRENGTH           12

#define BLUEMEN_NAME               "Blue Men"

class CharacterBlueMen : public CharacterBase
{
private:
  DiceCombo BlueMen2DefensePower;
  DiceCombo BlueMen1DefensePower;
  DiceCombo * CurrentDefenseDice;

public:
  CharacterBlueMen();
  ~CharacterBlueMen() { }

  void SetupAttackDice();
  void SetupDefenseDice();
  void SetupArmor();
  void SetupStrength();
  const char * GetName();
  unsigned int GenerateDefense();
  void DefendAttack(unsigned int damage);
};

#endif // CHARACTER_BLUEMEN_HPP
