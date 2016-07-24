#include "CharacterMedusa.hpp"
#include "lib_flip_display.hpp"

void CharacterMedusa::SetupAttackDice()
{
  AttackPower = DiceCombo (MEDUSA_NUM_ATTACK_DICE, MEDUSA_ATTACK_DICE_SIDES);
}

void CharacterMedusa::SetupDefenseDice()
{
  DefensePower = DiceCombo (MEDUSA_NUM_DEFENSE_DICE, MEDUSA_DEFENSE_DICE_SIDES);
}

void CharacterMedusa::SetupArmor()
{
  Armor = MEDUSA_ARMOR;
}

void CharacterMedusa::SetupStrength()
{
  Strength = MEDUSA_STRENGTH;
}

const char * CharacterMedusa::GetName()
{
    return MEDUSA_NAME;
}

CharacterMedusa::CharacterMedusa() : CharacterBase()
{
  DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Medusa\n");
  SetupAttackDice();
  SetupDefenseDice();
  SetupArmor();
  SetupStrength();
}
