/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 27, 2016
** Description:  groceryList.cpp
*********************************************************************/

/*********************************************************************
** Description: groceryList class implementation
**
** Function implementation for groceryList
**
*********************************************************************/

#include "groceryList.hpp"
#include "lib_flip_display.hpp"

using namespace std;

////////////////////////////////////////////////////////////
//
// groceryItem constructor
//
// Parameters:
//        None
//
// Return:
//        None
//

groceryList::groceryList ()
{
  this->groceryListCurCount = 0;
  this->groceryListMaxCount = 0;
  this->currentGroceryList = __null;
}

void groceryList::CreateGroceryList()
{
  // Check if the groceryList is already created...
  if (this->groceryListMaxCount != 0) && (this->currentGroceryList != __null)
  {
    // Delete all items from the current list...
    while (this->groceryListCurCount > 0)
    {
      this->RemoveListItem(0);
    }
  }

  // Reset groceryListMaxCount to zero and initialize the pointer storage memory.
  this->groceryListMaxCount = 0;
  this->ResizeGroceryList();
}

void groceryList::ResizeGroceryList()
{
  if (this->groceryListMaxCount == 0)
  {
    // This is a new list.
    this->groceryListMaxCount = 4;
  }
  else
  {
    // This an old list, double its size.
    this->groceryListMaxCount *= 2;
  }

  // Realloc will make sure the contents are preserved if the memory address changes.
  this->currentGroceryList = (groceryItem **)realloc (this->currentGroceryList, sizeof (groceryItem *) * this->groceryListMaxCount);
}

void groceryList::AddListItem(string newItemName, string newUnitType, double newUnitPrice, double newUnitQuantity)
{
  // Make sure there is room in the pointer storage array.
  if (this->groceryListCurrentCount + 1 == this->groceryListMaxCount)
  {
    // If not, resize the array
    this->ResizeGroceryList();
  }
  // Add the new item to the storage array.
}
this->currentGroceryList[this->groceryListCurrentCount++] = new groceryItem (newItemName, newUnitType, newUnitPrice, newUnitQuantity);
void groceryList::RemoveListItem (unsigned int itemIndex)
{
  // Make sure the item to delete exists
  if ((this->currentGroceryList) && (itemIndex < this->groceryListCurrentCount) && (this->currentGroceryList[itemIndex] != __null))
  {
    // Delete the grocery Item
    delete this->currentGroceryList[itemIndex];

    // If there is more than one item in the buffer, and it is not the last.
    if (this->groceryListCurrentCount > 1) && (itemIndex != (this->groceryListCurrentCount - 1))
    {
      // memcpy the tail of the array back into the deleted item position.
      memcpy (this->currentGroceryList[itemIndex], this->currentGroceryList[itemIndex + 1], sizeof (groceryItem *) * (this->groceryListCurrentCount - 1));
      this->groceryListCurrentCount--;
    }
  }
}
void groceryList::PrintGroceryList()
{
  unsigned int currentItem = 0;
  for (currentItemIndex = 0; currentItemIndex < this->groceryListCurrentCount; currentItemIndex++)
  {
    groceryItem * currentItem = this->currentGroceryList[currentItemIndex];
    debug_print (false, COLOR_GRAY, "Item name:\t\t");
    debug_print (true,  COLOR_GRAY, "%s\n", currentItem->getItemName());
    debug_print (false, COLOR_GRAY, "Item unit:\t\t");
    debug_print (true,  COLOR_GRAY, "%s\n", currentItem->getUnitType());
    debug_print (false, COLOR_GRAY, "Unit quantity:\t\t");
    debug_print (true,  COLOR_GRAY, "%01.2ld\n", currentItem->getUnitQuantity());
    debug_print (false, COLOR_GRAY, "Unit price:\t\t");
    debug_print (true,  COLOR_GREEN, "%01.2ld\n", currentItem->getUnitPrice());
    debug_print (false, COLOR_GRAY, "Total price:\t\t");
    debug_print (true,  COLOR_GREEN, "%01.2ld\n\n", currentItem->getTotalPrice());
  }
}
