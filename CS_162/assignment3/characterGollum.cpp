#include "CharacterGollum.hpp"
#include "lib_flip_display.hpp"

void CharacterGollum::SetupAttackDice()
{
  AttackPower = DiceCombo (GOLLUM_NUM_ATTACK_DICE, GOLLUM_ATTACK_DICE_SIDES);
}

void CharacterGollum::SetupDefenseDice()
{
  DefensePower = DiceCombo (GOLLUM_NUM_DEFENSE_DICE, GOLLUM_DEFENSE_DICE_SIDES);
}

void CharacterGollum::SetupArmor()
{
  Armor = GOLLUM_ARMOR;
}

void CharacterGollum::SetupStrength()
{
  Strength = GOLLUM_STRENGTH;
}

CharacterGollum::CharacterGollum() : CharacterBase()
{
  DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Gollum\n");
  SetupAttackDice();
  SetupDefenseDice();
  SetupArmor();
  SetupStrength();
}
