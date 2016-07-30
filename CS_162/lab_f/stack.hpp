#ifndef LAB_F_STACK_HPP
#define LAB_F_STACK_HPP

#include "lib_flip_display.hpp"

template <class T>
class Stack
{
public:
    struct StackNode
    {
        T data;
        struct StackNode * nextNode;
    };

private:
    struct StackNode * topOfStack;

public:
    Stack();
    ~Stack();

    void push(const T item);
    T peek();
    void pop();
    bool isEmpty();
};

template <class T>
Stack<T>::Stack()
{
    topOfStack = __null;
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Stack.\n");
}

template <class T>
Stack<T>::~Stack()
{
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Destroying Stack.\n");
    while (!isEmpty())
    {
        pop();
    }
}

template <class T>
void Stack<T>::push(const T item)
{
    if (isEmpty())
    {
        topOfStack = new StackNode();
        topOfStack->nextNode = __null;
    }
    else
    {
        StackNode * oldStackTop = topOfStack;
        topOfStack = new StackNode();
        topOfStack->nextNode = oldStackTop;
    }
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Pushing object on stack.\n");
    memcpy (&topOfStack->data, &item, sizeof (T));
}

template <class T>
T Stack<T>::peek()
{
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Peeking object on stack.\n");
    if (!isEmpty())
    {
        return topOfStack->data;
    }
    else
    {
        DebugConsole::debug_print (1, true, COLOR_YELLOW, "Stack is empty.\n");
        return (T)__null;
    }
}

template <class T>
void Stack<T>::pop()
{
    if (!isEmpty())
    {
        StackNode * nextNode = topOfStack->nextNode;
        delete topOfStack;
        topOfStack = nextNode;
        DebugConsole::debug_print (1, true, COLOR_CYAN, "Popping object from stack.\n");
        if (isEmpty())
        {
            DebugConsole::debug_print (1, true, COLOR_YELLOW, "Last object popped from stack.\n");
        }
    }   
}

template <class T>
bool Stack<T>::isEmpty()
{
    return (topOfStack == __null);
}

#endif // LAB_F_STACK_HPP