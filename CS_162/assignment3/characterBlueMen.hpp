#ifndef CHARACTER_BLUEMEN_HPP
#define CHARACTER_BLUEMEN_HPP

#include "characterBase.hpp"

#define BLUEMEN_NUM_ATTACK_DICE    2
#define BLUEMEN_ATTACK_DICE_SIDES  10
#define BLUEMEN_NUM_DEFENSE_DICE   3
#define BLUEMEN_DEFENSE_DICE_SIDES 6

#define BLUEMEN_ARMOR              3
#define BLUEMEN_STRENGTH           12

class CharacterBlueMen : public CharacterBase
{
public:
  CharacterBlueMen();
  ~CharacterBlueMen() { }

  void SetupAttackDice();
  void SetupDefenseDice();
  void SetupArmor();
  void SetupStrength();
};

#endif // CHARACTER_BLUEMEN_HPP
