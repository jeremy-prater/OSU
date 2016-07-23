/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 22, 2016
** Description:  assignment3.cpp
*********************************************************************/

#include <string>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "lib_flip_display.hpp"
#include "arg_parse.hpp"
#include "assignment3.hpp"

#include "CharacterMedusa.hpp"
#include "CharacterBlueMen.hpp"
#include "CharacterGollum.hpp"
#include "CharacterReptilePeople.hpp"
#include "CharacterHarryPotter.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// int main()
//
// Program entry point.
//
// Parameters:
//        int argc - number of command line parameters
//        char * argvp[] - char array of command line parameters
//
// Return:
//        int return code - zero for success
//

int main(int argc, char * argv[])
{
    // Parse command line rguments
    customArgParser::InitalizeArguments();
    argp_parse (&customArgParser::argp, argc, argv, 0, 0, &customArgParser::arguments);

    debug_print (0, true, COLOR_GREEN, "Welcome to CS_162 Battle Arena (assignment 3)!!\n\n")

    if (customArguments::arguments.enableDebug == true)
    {
      setdebuglevel (1);
    }
    int characterSelect = 0;
    while (characterSelect == 0)
    {
      debug_print (0, true, COLOR_WHITE, "Choose your character\n");
      debug_print (0, true, COLOR_WHITE, "---------------------\n");
      debug_print (0, true, COLOR_WHITE, "1. Medusa\n");
      debug_print (0, true, COLOR_WHITE, "2. Gollum\n");
      debug_print (0, true, COLOR_WHITE, "3. Reptile People\n");
      debug_print (0, true, COLOR_WHITE, "4. Blue Men\n");
      debug_print (0, true, COLOR_WHITE, "5. Harry Potter\n");
      if (GetDebugLevel() == 0)
      {
        debug_print (0, true, COLOR_WHITE, "D. Enable Debug output\n");
      }
      debug_print (0, false, COLOR_WHITE, "Enter Selection: ");
    }

    CharacterMedusa medusa;
    CharacterBlueMen bluemen;
    CharacterGollum gollum;
    CharacterReptilePeople reptilepeople;
    CharacterHarryPotter harrypotter;

    return 0;
}
