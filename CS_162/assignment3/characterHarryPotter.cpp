#include "CharacterHarryPotter.hpp"
#include "lib_flip_display.hpp"

void CharacterHarryPotter::SetupAttackDice()
{
  AttackPower = DiceCombo (HARRY_POTTER_NUM_ATTACK_DICE, HARRY_POTTER_ATTACK_DICE_SIDES);
}

void CharacterHarryPotter::SetupDefenseDice()
{
  DefensePower = DiceCombo (HARRY_POTTER_NUM_DEFENSE_DICE, HARRY_POTTER_DEFENSE_DICE_SIDES);
}

void CharacterHarryPotter::SetupArmor()
{
  Armor = HARRY_POTTER_ARMOR;
}

void CharacterHarryPotter::SetupStrength()
{
  Strength = HARRY_POTTER_STRENGTH;
  usedHogWarts = false;
}

const char * CharacterHarryPotter::GetName()
{
    return HARRY_POTTER_NAME;
}

CharacterHarryPotter::CharacterHarryPotter() : CharacterBase()
{
  DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Harry Potter\n");
  SetupAttackDice();
  SetupDefenseDice();
  SetupArmor();
  SetupStrength();
}

void CharacterHarryPotter::DefendAttack(unsigned int damage)
{
  CharacterBase::DefendAttack(damage);
  if ((Strength == 0) && (usedHogWarts == false))
  {
    DebugConsole::debug_print (0, true, COLOR_MAGENTA, "Harry Potter used Hogwarts!\n");
    usedHogWarts = true;
    Strength = HARRY_POTTER_STRENGTH;
  }
}
