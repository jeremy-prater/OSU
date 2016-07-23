#include "CharacterMedusa.hpp"

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

CharacterMedusa::CharacterMedusa() : CharacterBase()
{
  SetupAttackDice();
  SetupDefenseDice();
  SetupArmor();
  SetupStrength();
}
