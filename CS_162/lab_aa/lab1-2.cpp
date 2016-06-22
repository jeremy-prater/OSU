/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 21, 2016
** Description:  Lab Aa
*********************************************************************/

#include "summation.h"
#include "lib_flip_display.h"
#include <stdlib.h>


/*********************************************************************
** Description: Lab Aa lab1-2.cpp
**
** Implementation for lab1-2.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// int main (void)
//
// Program entry point for lab1-2.cpp
//

int main (void)
{
  init_display();
  debug_print (true, COLOR_GREEN, "CS_162: Lab Aa 1-2 Testing...\n\n");
  
  double testResult;
  double testArray1[10] = {0,1,2,3,4,5,6,7,8,9};
  
  unsigned int userArrayLength;
  double * userArray;
  
  debug_print (false, COLOR_WHITE, "Summation of zero length array...");
  debug_test_result (sum (testArray1, 0) == 0);

  debug_print (false, COLOR_WHITE, "Summation of nullptr array...");
  debug_test_result (sum (__null, ARRAY_SIZE (testArray1)) == 0);
  
  debug_print (false, COLOR_WHITE, "Summation of testArray1...");
  debug_test_result (sum (testArray1, ARRAY_SIZE (testArray1)) == 45);

  debug_print (false, COLOR_WHITE, "Summation of testArray1 with incorrect length...");
  debug_test_result (sum (testArray1, ARRAY_SIZE (testArray1)-1) != 45);
  
  debug_print (false, COLOR_WHITE,"Enter user defined array test:\n\nEnter number of elements: ");

  scanw ("%d", &userArrayLength);

  userArray = (double*)malloc (userArrayLength * sizeof (double));
  for (unsigned int userCount = 0;userCount < userArrayLength; userCount++)
  {
    debug_print (false, COLOR_WHITE,"Enter data (%u/%u): ", userCount+1, userArrayLength);
    scanw ("%lf", &userArray[userCount]);
  }

  debug_print (false, COLOR_WHITE, "User Sum : %lf\n\n", sum(userArray, userArrayLength));

  free (userArray);

  debug_print (false, COLOR_WHITE, "Test Complete! Press any key to exit.");
  getch();
  shutdown_display();
  return 0;
}
