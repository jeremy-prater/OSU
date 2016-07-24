#include "CharacterBase.hpp"

unsigned int CharacterBase::GenerateAttack()
{
  return AttackPower.RollAllDice();
}

unsigned int CharacterBase::GenerateDefense()
{
  return DefensePower.RollAllDice();
}

void CharacterBase::DefendAttack(unsigned int damage)
{
  int defense = GenerateDefense() + Armor;

  // Cap defense at the incoming damage
  if (defense > damage)
  {
    defense = damage;
  }

  if ((damage - defense) >= Strength)
  {
    // Character has died...
    Strength = 0;
  }
  else
  {
    // Character injured, but still alive
    Strength -= (damage - defense);
  }
}

unsigned int CharacterBase::GetStrength()
{
  return Strength;
}
