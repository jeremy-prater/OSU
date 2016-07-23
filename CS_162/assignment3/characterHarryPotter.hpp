#ifndef CHARACTER_HARRY_POTTER_HPP
#define CHARACTER_HARRY_POTTER_HPP

#include "characterBase.hpp"

#define HARRY_POTTER_NUM_ATTACK_DICE    2
#define HARRY_POTTER_ATTACK_DICE_SIDES  6
#define HARRY_POTTER_NUM_DEFENSE_DICE   2
#define HARRY_POTTER_DEFENSE_DICE_SIDES 6

#define HARRY_POTTER_ARMOR              0
#define HARRY_POTTER_STRENGTH           10
#define HARRY_POTTER_STRENGTH_HOGWARTS  20

class CharacterHarryPotter : public CharacterBase
{
public:
  CharacterHarryPotter();
  ~CharacterHarryPotter() { }

  void SetupAttackDice();
  void SetupDefenseDice();
  void SetupArmor();
  void SetupStrength();
};

#endif // CHARACTER_HARRY_POTTER_HPP
