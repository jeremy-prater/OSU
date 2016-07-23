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

    CharacterMedusa medusa;
    return 0;
}
