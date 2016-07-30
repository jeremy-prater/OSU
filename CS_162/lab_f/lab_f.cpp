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

    myStack.push (1);
    myStack.push (2);
    myStack.push (3);

    DebugConsole::debug_print (0, true, COLOR_WHITE, "stack pop: %d\n", myStack.peek());
    myStack.pop();

    myStack.push (4);
    myStack.push (5);

    while (!myStack.isEmpty())
    {
      DebugConsole::debug_print (0, true, COLOR_WHITE, "stack pop: %d\n", myStack.peek());
      myStack.pop();
    }

    myStack.push (6);
    myStack.push (7);
    myStack.push (8);
    
    myQueue.addBack(1);
    myQueue.addBack(2);
    myQueue.addBack(3);

    DebugConsole::debug_print (0, true, COLOR_WHITE, "queue getFront: %d\n", myQueue.getFront());
    myQueue.removeFront();

    myQueue.addBack(4);
    myQueue.addBack(5);

    while (!myQueue.isEmpty())
    {
      DebugConsole::debug_print (0, true, COLOR_WHITE, "queue getFront: %d\n", myQueue.getFront());
      myQueue.removeFront();
    }

    myQueue.addBack(6);
    myQueue.addBack(7);
    myQueue.addBack(8);

    while (!myStack.isEmpty())
    {
      DebugConsole::debug_print (0, true, COLOR_WHITE, "stack pop: %d\n", myStack.peek());
      myStack.pop();
    }
    while (!myQueue.isEmpty())
    {
      DebugConsole::debug_print (0, true, COLOR_WHITE, "queue getFront: %d\n", myQueue.getFront());
      myQueue.removeFront();
    }

    myStack.push (10);
    myStack.push (11);
    myStack.push (12);
    myQueue.addBack(10);
    myQueue.addBack(11);
    myQueue.addBack(12);


    return 0;
}