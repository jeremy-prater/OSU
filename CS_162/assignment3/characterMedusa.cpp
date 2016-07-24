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

unsigned int CharacterMedusa::GenerateAttack()
{
  int damage = CharacterBase::GenerateAttack();
  if (damage == 12)
  {
    DebugConsole::debug_print (0, true, COLOR_MAGENTA, "Medusa used GLARE!\n");
    return 9999;
  }
  return damage;
}
