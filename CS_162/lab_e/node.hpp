/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 9, 2016
** Description:  lab-c.hpp
*********************************************************************/

#ifndef LAB_E_NODE_H
#define LAB_E_NODE_H

//////////////////////////////////////////////////////////////////////
//
// Node Class
//
// A basic class for storing a char in a linked list
//

class Node
{
private:
    Node * nextNode;
    char payloadData;

public:
    Node(char newData);
    ~Node() { }

    char GetNodeData();

    void SetNextNode (Node * next);
    Node * GetNextNode ();
};

//////////////////////////////////////////////////////////////////////
//
// Node Controller Class
//
// A class for managing the linked list and using its contents.
//

class NodeController
{
private:
    Node * headNode;
    Node * currentNode;
    Node * lastNode;

    bool isLastNode;

    char GetNodeData ();
    void RemoveNode ();
    void DeleteNode ();

public:
    NodeController();
    ~NodeController();

    Node * AddNode (char dataToAdd);
    char GetNodeDataAndRemove();

    void PrintSingleItem();
    void PrintAllItems();
};


#endif // LAB_E_NODE_H
