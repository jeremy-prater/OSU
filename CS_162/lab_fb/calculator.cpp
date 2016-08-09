#include "calculator.hpp"
#include "lib_flip_display.hpp"

Calculator::Calculator()
{
    stackDepth = 0;
    running = true;
    calcStack = new Stack;
}

Calculator::~Calculator()
{
    delete calcStack;
}

void Calculator::add()
{
    if (stackDepth >= 2)
    {
        int value1 = calcStack->peek(); calcStack->pop();
        int value2 = calcStack->peek(); calcStack->pop();
        calcStack->push (value1 + value2);
    }
    else
    {
        DebugConsole::debug_print (0, true, COLOR_RED, "Input Error. Insufficent input for %s", __func__);
    }
}

void Calculator::subtract()
{
    if (stackDepth >= 2)
    {
        int value1 = calcStack->peek(); calcStack->pop();
        int value2 = calcStack->peek(); calcStack->pop();
        calcStack->push (value1 - value2);
    }
    else
    {
        DebugConsole::debug_print (0, true, COLOR_RED, "Input Error. Insufficent input for %s", __func__);
    }
}

void Calculator::multiply()
{
    if (stackDepth >= 2)
    {
        int value1 = calcStack->peek(); calcStack->pop();
        int value2 = calcStack->peek(); calcStack->pop();
        calcStack->push (value1 * value2);
    }
    else
    {
        DebugConsole::debug_print (0, true, COLOR_RED, "Input Error. Insufficent input for %s", __func__);
    }
}

void Calculator::divide()
{
    if (stackDepth >= 2)
    {
        int value1 = calcStack->peek(); calcStack->pop();
        int value2 = calcStack->peek(); calcStack->pop();
        calcStack->push (value1 / value2);
    }
    else
    {
        DebugConsole::debug_print (0, true, COLOR_RED, "Input Error. Insufficent input for %s", __func__);
    }
}

void Calculator::PrintStack()
{
    DebugConsole::debug_print (0, true, COLOR_CYAN, "Stack Depth: %d. Stack Contents:\n\n", stackDepth);
    Stack * newStack = new Stack;
    while (!calcStack->isEmpty())
    {
        DebugConsole::debug_print (0, false, COLOR_WHITE, "\t%d\n", calcStack->peek());
        calcStack->pop();
    }
    delete calcStack;
    calcStack = newStack;

    // Now the stack is reversed...
    newStack = new Stack;
    while (!calcStack->isEmpty())
    {
        calcStack->pop();
    }
    delete calcStack;
    
    // Now the stack is back to normal.
    calcStack = newStack;
    DebugConsole::debug_print (0, false, COLOR_WHITE, "\n\n");
}

void Calculator::ProcessInput()
{
    std::string input;
    DebugConsole::debug_print (0, false, COLOR_WHITE, "\tEnter Input >");
    std::cin >> input;
    char * resultString;
    long numberInput = strtol(input.c_str(), &resultString, 10);
    DebugConsole::debug_print(0, false, "%x:%x:%d:%s - %d\n\n", input.c_str(), resultString, *resultString, resultString, numberInput);
    if (resultString == 0)
    {
        // The result is a number.
        // Push it onto the stack.
        calcStack->push (numberInput);
        stackDepth++;
    }
    else
    {
        // The result is a string. Compare it to +-*/
        if (input.compare ("+") == 0)
        {
            add();
        }
        if (input.compare ("-") == 0)
        {
            subtract();
        }
        if (input.compare ("*") == 0)
        {
            multiply();
        }
        if (input.compare ("/") == 0)
        {
            divide();
        }
        if (input.compare ("q") == 0)
        {
            running = false;
        }
    }
}

void Calculator::CalculatorLoop()
{
    while (running)
    {
        ProcessInput();
        PrintStack();
    }
}
