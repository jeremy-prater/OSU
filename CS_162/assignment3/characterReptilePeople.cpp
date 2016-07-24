#include "CharacterReptilePeople.hpp"
#include "lib_flip_display.hpp"

void CharacterReptilePeople::SetupAttackDice()
{
  AttackPower = DiceCombo (REPTILE_PEOPLE_NUM_ATTACK_DICE, REPTILE_PEOPLE_ATTACK_DICE_SIDES);
}

void CharacterReptilePeople::SetupDefenseDice()
{
  DefensePower = DiceCombo (REPTILE_PEOPLE_NUM_DEFENSE_DICE, REPTILE_PEOPLE_DEFENSE_DICE_SIDES);
}

void CharacterReptilePeople::SetupArmor()
{
  Armor = REPTILE_PEOPLE_ARMOR;
}

void CharacterReptilePeople::SetupStrength()
{
  Strength = REPTILE_PEOPLE_STRENGTH;
}

const char * CharacterReptilePeople::GetName()
{
    return REPTILE_PEOPLE_NAME;
}

CharacterReptilePeople::CharacterReptilePeople() : CharacterBase()
{
  DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Reptile People\n");
  SetupAttackDice();
  SetupDefenseDice();
  SetupArmor();
  SetupStrength();
}
