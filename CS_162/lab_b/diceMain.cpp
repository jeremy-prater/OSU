#include "dice.hpp"
#include "lib_flip_display.hpp"
#include <iostream>
#include <fstream>

int main ()
{
  debug_print (true, COLOR_CYAN, "Dice/LoadedDice data generator V1.0\n\n");

  // Create some dice...
  Dice dice6();
  Dice dice();

  ofstream diceOut;
  diceOut.open ("dice_out_10.csv");
  diceout << "Roll\n";
  for (int rollCounter = 0, rollCounter < 10; rollCounter++)
  {
    diceout << dice6.Roll() << "\n";
  }
  diceOut.close();
  debug_print ("Saved dice_out_10.csv");

  return 0;
}
