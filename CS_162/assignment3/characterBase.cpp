#include "CharacterBase.hpp"
#include "lib_flip_display.hpp"

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
    DebugConsole::debug_print (0, true, COLOR_RED, "%s took %d damage and died!\n", this->GetName(), (damage - defense));
    Strength = 0;
  }
  else
  {
    // Character injured, but still alive
    Strength -= (damage - defense);
    DebugConsole::debug_print (0, false, COLOR_YELLOW, "%s took %d damage!\n", this->GetName(), (damage - defense));
  }
}

unsigned int CharacterBase::GetStrength()
{
  return Strength;
}
