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

#include "stack.hpp"
#include "queue.hpp"

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

    // Exit and return success.
    return 0;
}
