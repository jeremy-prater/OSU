#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "stack.hpp"

class Calculator
{
private:
    Stack calcStack;

public:
    void PrintStack();
    void ProcessInput();
    void CalculatorLoop();
}

#endif // CALCULATOR_HPP