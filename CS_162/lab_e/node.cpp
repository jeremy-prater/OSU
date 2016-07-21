#include "node.hpp"
#include <iostream>


Node::Node (char newData)
{
    payloadData = newData;
    nextNode = __null;
}

void Node::SetNextNode(Node * next)
{
    nextNode = next;
}

Node * Node::GetNextNode()
{
    return nextNode;
}

char Node::GetNodeData()
{
    return payloadData;
}

NodeController::NodeController()
{
    headNode = __null;
    lastNode = __null;
    currentNode = __null;
    isLastNode = true;
}

NodeController::~NodeController()
{
    while (headNode != __null)
    {
        DeleteNode();
    }
}

Node * NodeController::AddNode (char dataToAdd)
{
    if (headNode == __null)
    {
        // This is the first Add case.
        headNode = new Node (dataToAdd);
        headNode->SetNextNode(headNode);
        currentNode = headNode;
        lastNode = headNode;
    }
    else
    {
        // Adding nodes to the chain.
        lastNode->SetNextNode (new Node (dataToAdd));
        lastNode = lastNode->GetNextNode();
        lastNode->SetNextNode (headNode);
    }
    isLastNode = false;
}

char NodeController::GetNodeData ()
{
    if (isLastNode)
    {
        return 0;
    }
    else
    {
        return currentNode->GetNodeData();
    }
}

void NodeController::RemoveNode ()
{
    if (currentNode->GetNextNode() == headNode)
    {
        isLastNode = true;
    }
    else
    {
        currentNode = currentNode->GetNextNode();
    }
}

void NodeController::DeleteNode ()
{
    // Check if this is the last node!
    if (lastNode == headNode)
    {
        delete headNode;
        headNode = __null;
        lastNode = __null;
        currentNode = __null;
    }
    else
    {
        // Re-assign last->next to head->next
        lastNode->SetNextNode(headNode->GetNextNode());

        // If the current node is the head node
        if (currentNode == headNode)
        {
            // Move the current node to the next one.
            currentNode = headNode->GetNextNode();
        }
        // Delete the Node
        delete headNode;

        // Reset headNode to the new head.
        headNode = lastNode->GetNextNode();
    }
}

char NodeController::GetNodeDataAndRemove()
{
    char data = GetNodeData();
    RemoveNode();
    return data;
}

void NodeController::PrintSingleItem()
{
    if (currentNode != __null)
    {
        std::cout << GetNodeDataAndRemove();
    }
}

void NodeController::PrintAllItems()
{
    while (isLastNode == false)
    {
        PrintSingleItem();
    }
}
