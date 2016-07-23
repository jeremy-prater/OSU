#ifndef CHARACTER_MEDUSA_HPP
#define CHARACTER_MEDUSA_HPP

#include "characterBase.hpp"

#define MEDUSA_NUM_ATTACK_DICE    2
#define MEDUSA_ATTACK_DICE_SIDES  6
#define MEDUSA_NUM_DEFENSE_DICE   1
#define MEDUSA_DEFENSE_DICE_SIDES 6

#define MEDUSA_ARMOR              3
#define MEDUSA_STRENGTH           8

class CharacterMedusa : public CharacterBase
{
public:
  CharacterMedusa();
  ~CharacterMedusa() { }

  void SetupAttackDice();
  void SetupDefenseDice();
  void SetupArmor();
  void SetupStrength();
};

#endif // CHARACTER_MEDUSA_HPP
