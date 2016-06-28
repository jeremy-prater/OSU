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


  shutdown_display();
  return 0;
}
