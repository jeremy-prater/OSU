/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 27, 2016
** Description:  groceryMain.cpp
*********************************************************************/

#include "groceryList.hpp"
#include "lib_flip_display.hpp"

/*********************************************************************
** Description: groceryMain implementation
**
**
*********************************************************************/

using namespace std;

////////////////////////////////////////////////////////////
//
// int main() - program entry point
//
// Parameters:
//        None
//
// Return:
//        Success
//

int main()
{
  init_display();
  debug_print (true, COLOR_CYAN, "Grocery List V1.0 Testing...\n\n");

  groceryList * myList = new groceryList();

  debug_print (false, COLOR_WHITE, "Remove all items from empty storage.\t\t\t\n");
  myList->RemoveAllListItems();
  debug_test_result (myList->GetItemCount() == 0);

  debug_print (false, COLOR_WHITE, "Remove item(0) from empty storage.\t\t\t\n");
  myList->RemoveListItem(0);
  debug_test_result (myList->GetItemCount() == 0);

  debug_print (false, COLOR_WHITE, "Total price from empty storage.\t\t\t\n");
  debug_test_result (myList->getTotalPrice() == 0);


  myList->AddListItem ("Bananas", "lb", 0.99, 2.32);
  myList->AddListItem ("Tomatoes", "ea", 0.99, 4);
  myList->AddListItem ("Life cereal", "box", 3.19, 1);
  myList->AddListItem ("Frozen pizza", "ea", 6.79, 2);
  myList->AddListItem ("Apples", "lb", 0.79, 180);
  myList->AddListItem ("Ice cream", "pack", 5.19, 1);

  myList->PrintGroceryList();

  delete myList;
  debug_print (false, COLOR_WHITE, "Test Complete! Press any key to exit.");
  getch();
  shutdown_display();
  return 0;
}
