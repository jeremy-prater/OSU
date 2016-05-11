/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 9, 2016
** Description:  Module 7 assignment
*********************************************************************/

#include <math.h>
#include <vector>

#ifdef Debug
#include <iostream>
#include"stdio.h"
#endif

#include "findMode.hpp"

/*********************************************************************
** Description: Assignment 7
**
** Create a function called findMode to find the frequency of integers
**
*********************************************************************/

/*********************************************************************
** findMode Function Definitions
**
*********************************************************************/

std::vector<int> findMode (int input[], int length);

/////////////////////////////////////////////////////////////////
//
// findMode Functions
//
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//
// std::std::vector<int[]> findMode (int[] input)
//
// Return a vector (int[]) with the mode(s) of input (int[]).
//

std::vector<int> findMode (int input[], int length)
{
  std::vector<int_frequency> temp_data;

  for (int i=0; i<length; i++)
  {
    struct int_frequency temp_storage;

    // Find or create a new frequency counter for input[i]
    bool found = false;
    for (int x = 0; x < temp_data.size(); x++)
    {
      printf ("Start %d\n", x);
      if (temp_data[x].value == input[i])
      {
        // Node found.
        temp_data[x].count++;
        printf ("Mod %d:%d\n", x, temp_data[x].count);
        found = true;
      }
    }
    if (temp_data.size() == 0 || !found)
    {
      // Create and assign node.
      temp_storage.value = input[i];
      temp_storage.count = 1;
      printf ("Adding %d:%d\n", temp_storage.value, temp_storage.count);
      temp_data.push_back(temp_storage);
    }
  }
}


#ifdef Debug
int main()
{
  int test1[] = {1,1,1,1,1,2};
  int test2[] = {1,1,1,2,2,2};
  int test3[] = {1,2,3,4,5,6};
  int test4[] = {1,1,2,2,3,3};

  printf ("Starting...\n");

  std::vector<int> result1 = findMode(test1, sizeof (test1));
  for (int x=0;x<result1.size();x++)
  {
    printf ("loop: %d=%d\n",x ,result1[x]);
  }

  std::vector<int> result2 = findMode(test1, sizeof (test2));
  std::vector<int> result3 = findMode(test1, sizeof (test3));
  std::vector<int> result4 = findMode(test1, sizeof (test4));


  //std::cout << "Distance : " << dist << std::endl;

  return 0;
}
#endif
