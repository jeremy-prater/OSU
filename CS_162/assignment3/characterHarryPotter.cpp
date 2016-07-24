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
}

CharacterHarryPotter::CharacterHarryPotter() : CharacterBase()
{
  DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Harry Potter\n");
  SetupAttackDice();
  SetupDefenseDice();
  SetupArmor();
  SetupStrength();
}
