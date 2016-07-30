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
    headNode = __null;
    tailNode = __null;
}

template <class T>
Queue<T>::~Queue()
{
    while (!isEmpty())
    {
        removeFront();
    }
}

template <class T>
void Queue<T>::addBack(const T item)
{
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
    if (!isEmpty())
    {
        return headNode->data;
    }
    else
    {
        return (T)__null;
    }
}

template <class T>
void Queue<T>::removeFront()
{
    if (!isEmpty())
    {
        QueueNode * nextNode = headNode->nextNode;
        delete headNode;
        if (tailNode == headNode)
        {
            tailNode = nextNode;
        }
        headNode = nextNode;        
    }   
}

template <class T>
bool Queue<T>::isEmpty()
{
    return (headNode == __null);
}

#endif // LAB_F_QUEUE_HPP