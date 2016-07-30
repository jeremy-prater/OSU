/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 22, 2016
** Description:  lab_f.cpp
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

    DebugConsole::debug_print (0, true, COLOR_GREEN, "CS_162 lab_f\n\n");

    if (customArgParser::arguments.debugEnable == true)
    {
      DebugConsole::SetDebugLevel (1);
    }

    Queue<int> myQueue;
    Stack<int> myStack;

    myQueue.getFront();
    myQueue.removeFront();
    
    myStack.peek();
    myStack.pop();

    return 0;
}
