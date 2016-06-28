/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 27, 2016
** Description:  groceryList.hpp
*********************************************************************/

#ifndef GROCERY_LIST
#define GROCERY_LIST

#include "groceryItem.hpp"

/*********************************************************************
** Description: groceryItem class definition
**
** Function declarations for average.cpp
**
*********************************************************************/

using namespace std;

class groceryList
{
private:
  unsigned int groceryListMaxCount;
  unsigned int groceryListCurrentCount;
  groceryItem ** currentGroceryList;

  void ResizeGroceryList();
  void RemoveAllListItems();

public:
  groceryList ();
  groceryList::~groceryList()

  void CreateGroceryList();
  void AddListItem(string newItemName, string newUnitType, double newUnitPrice, double newUnitQuantity);
  void RemoveListItem (unsigned int itemIndex);
  void PrintGroceryList();
};

#endif // GROCERY_LIST
