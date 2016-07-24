#include "CharacterBlueMen.hpp"
#include "lib_flip_display.hpp"

void CharacterBlueMen::SetupAttackDice()
{
  AttackPower = DiceCombo (BLUEMEN_NUM_ATTACK_DICE, BLUEMEN_ATTACK_DICE_SIDES);
}

void CharacterBlueMen::SetupDefenseDice()
{
  DefensePower = DiceCombo (BLUEMEN_NUM_DEFENSE_DICE, BLUEMEN_DEFENSE_DICE_SIDES);
}

void CharacterBlueMen::SetupArmor()
{
  Armor = BLUEMEN_ARMOR;
}

void CharacterBlueMen::SetupStrength()
{
  Strength = BLUEMEN_STRENGTH;
}

CharacterBlueMen::CharacterBlueMen() : CharacterBase()
{
  DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating BlueMen\n");
  SetupAttackDice();
  SetupDefenseDice();
  SetupArmor();
  SetupStrength();
}
