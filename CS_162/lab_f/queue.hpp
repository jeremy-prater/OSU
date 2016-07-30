#ifndef LAB_F_QUEUE_HPP
#define LAB_F_QUEUE_HPP

template <class T>
class Queue
{
public:
    struct QueueNode
    {
        T data;
        struct QueueNode * nextNode;
    };

private:
    struct QueueNode * headNode;
    struct QueueNode * tailNode;

public:
    Queue();
    ~Queue();

    void addBack(const T item);
    T getFront();
    void removeFront();
    bool isEmpty();
};

template <class T>
Queue<T>::Queue()
{
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Queue.\n");
    headNode = __null;
    tailNode = __null;
}

template <class T>
Queue<T>::~Queue()
{
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Destroying Queue.\n");
    while (!isEmpty())
    {
        removeFront();
    }
}

template <class T>
void Queue<T>::addBack(const T item)
{
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Adding object to Queue.\n");
    if (isEmpty())
    {
        headNode = tailNode = new QueueNode();
    }
    else
    {
        tailNode->nextNode = new QueueNode();
        tailNode = tailNode->nextNode;
    }
    memcpy (&tailNode->data, &item, sizeof (T));
    tailNode->nextNode = __null;
}

template <class T>
T Queue<T>::getFront()
{
    DebugConsole::debug_print (1, true, COLOR_CYAN, "Getting head object from Queue.\n");
    if (!isEmpty())
    {
        return headNode->data;
    }
    else
    {
        DebugConsole::debug_print (1, true, COLOR_YELLOW, "Queue is empty.\n");
        return (T)__null;
    }
}

template <class T>
void Queue<T>::removeFront()
{
    if (!isEmpty())
    {
        DebugConsole::debug_print (1, true, COLOR_CYAN, "Removing head object from Queue.\n");
        QueueNode * nextNode = headNode->nextNode;
        delete headNode;
        headNode = nextNode;
        if (isEmpty())
        {
            DebugConsole::debug_print (1, true, COLOR_YELLOW, "Last object removed from Queue.\n");
            tailNode = __null;
        }                
    }   
}

template <class T>
bool Queue<T>::isEmpty()
{
    return (headNode == __null);
}

#endif // LAB_F_QUEUE_HPP