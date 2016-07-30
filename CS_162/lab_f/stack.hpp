#ifndef LAB_F_STACK_HPP
#define LAB_F_STACK_HPP

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
}

template <class T>
Stack<T>::~Stack()
{
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
    }
    else
    {
        topOfStack->nextNode = new StackNode();
        topOfStack = topOfStack->nextNode;
    }
    memcpy (&topOfStack->data, &item, sizeof (T));
    topOfStack->nextNode = __null;
}

template <class T>
T Stack<T>::peek()
{
    if (!isEmpty())
    {
        return topOfStack->data;
    }
    else
    {
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
    }   
}

template <class T>
bool Stack<T>::isEmpty()
{
    return (topOfStack == __null);
}

#endif // LAB_F_STACK_HPP