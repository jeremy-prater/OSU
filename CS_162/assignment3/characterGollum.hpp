#ifndef CHARACTER_GOLLUM_HPP
#define CHARACTER_GOLLUM_HPP

#include "characterBase.hpp"

#define GOLLUM_NUM_ATTACK_DICE    1
#define GOLLUM_ATTACK_DICE_SIDES  6
#define GOLLUM_NUM_DEFENSE_DICE   1
#define GOLLUM_DEFENSE_DICE_SIDES 6

#define GOLLUM_NUM_JUMP_DICE    3
#define GOLLUM_JUMP_DICE_SIDES  6

#define GOLLUM_ARMOR              3
#define GOLLUM_STRENGTH           8

#define GOLLUM_NAME               "Gollum"

class CharacterGollum : public CharacterBase
{
private:
  DiceCombo JumpPower;
public:
  CharacterGollum();
  ~CharacterGollum() { }

  void SetupAttackDice();
  void SetupDefenseDice();
  void SetupArmor();
  void SetupStrength();
  const char * GetName();

  unsigned int GenerateAttack();
};

#endif // CHARACTER_GOLLUM_HPP
