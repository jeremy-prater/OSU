#include "CharacterGollum.hpp"
#include "lib_flip_display.hpp"
#include <stdlib.h>

void CharacterGollum::SetupAttackDice()
{
  AttackPower = DiceCombo (GOLLUM_NUM_ATTACK_DICE, GOLLUM_ATTACK_DICE_SIDES);
  JumpPower = DiceCombo (GOLLUM_NUM_JUMP_DICE, GOLLUM_JUMP_DICE_SIDES);
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

const char * CharacterGollum::GetName()
{
    return GOLLUM_NAME;
}

CharacterGollum::CharacterGollum() : CharacterBase()
{
  DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Gollum\n");
  SetupAttackDice();
  SetupDefenseDice();
  SetupArmor();
  SetupStrength();
}

unsigned int CharacterGollum::GenerateAttack()
{
  // Generate a number between 1 - 100
  int jumpChance = (rand() % 100) + 1;
  if (jumpChance > 5)
  {
    return AttackPower.RollAllDice();
  }
  else
  {
    DebugConsole::debug_print (0, true, COLOR_MAGENTA, "Gollum used Jump!\n");
    return JumpPower.RollAllDice();
  }
}
