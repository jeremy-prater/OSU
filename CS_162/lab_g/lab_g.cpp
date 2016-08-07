/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 31, 2016
** Description:  lab_g.cpp
*********************************************************************/

#include <string>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "lib_flip_display.hpp"
#include "lib_arg_parse.hpp"

#include "fileLoader.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// Local function definitions
//


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


    if (customArgParser::arguments.debugEnable == true)
    {
      DebugConsole::SetDebugLevel (1);
    }

    DebugConsole::debug_print (0, true, COLOR_GREEN, "CS_162 lab_g\n\n");

    fileLoader loader("rand_integer.txt");
    fileLoader loader0("rand_integer_0.txt");

    int searchValue;
    DebugConsole::debug_print (0, false, COLOR_WHITE, "Linear search for values in rand_integer.txt\n\nEnter value to find: ");
    cin >> searchValue;
    loader.LinearSearch(searchValue);

    loader.BubbleSort();

    loader.SaveData("rand_integer_sorted.txt");

    DebugConsole::debug_print (0, false, COLOR_WHITE, "Binary search for values in rand_integer_sorted.txt\n\nFinding 0.\n\n");    
    searchValue = 0;
    loader.BinarySearch(searchValue);

    DebugConsole::debug_print (0, false, COLOR_WHITE, "Binary search for values in rand_integer_sorted.txt\n\nEnter value to find: ");
    cin >> searchValue;
    loader.BinarySearch(searchValue);

    DebugConsole::debug_print (0, false, COLOR_WHITE, "Linear search for values in rand_integer_0.txt\n\nEnter value to find: ");
    cin >> searchValue;
    loader0.LinearSearch(searchValue);

    loader0.BubbleSort();

    loader0.SaveData("rand_integer_0_sorted.txt");

    DebugConsole::debug_print (0, false, COLOR_WHITE, "Binary search for values in rand_integer_0_sorted.txt\n\nFinding 0.\n\n");    
    searchValue = 0;
    loader0.BinarySearch(searchValue);

    DebugConsole::debug_print (0, false, COLOR_WHITE, "Binary search for values in rand_integer_0_sorted.txt\n\nEnter value to find: ");
    cin >> searchValue;
    loader0.BinarySearch(searchValue);
    // Exit and return success.
    return 0;
}
