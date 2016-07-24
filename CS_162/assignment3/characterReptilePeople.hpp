#ifndef CHARACTER_REPTILE_PEOPLE_HPP
#define CHARACTER_REPTILE_PEOPLE_HPP

#include "characterBase.hpp"

#define REPTILE_PEOPLE_NUM_ATTACK_DICE    3
#define REPTILE_PEOPLE_ATTACK_DICE_SIDES  6
#define REPTILE_PEOPLE_NUM_DEFENSE_DICE   1
#define REPTILE_PEOPLE_DEFENSE_DICE_SIDES 6

#define REPTILE_PEOPLE_ARMOR              7
#define REPTILE_PEOPLE_STRENGTH           18

#define REPTILE_PEOPLE_NAME               "Reptile People"

class CharacterReptilePeople : public CharacterBase
{
public:
  CharacterReptilePeople();
  ~CharacterReptilePeople() { }

  void SetupAttackDice();
  void SetupDefenseDice();
  void SetupArmor();
  void SetupStrength();
  const char * GetName();
};

#endif // CHARACTER_REPTILE_PEOPLE_HPP
