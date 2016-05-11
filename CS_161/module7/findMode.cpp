/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 9, 2016
** Description:  Module 7 assignment
*********************************************************************/

#include <math.h>
#include <vector>
#include <algorithm>

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
  std::vector<int> output_data;

  for (int i=0; i<length; i++)
  {
    struct int_frequency temp_storage;

    // Find or create a new frequency counter for input[i]
    bool found = false;
    for (int x = 0; x < temp_data.size(); x++)
    {
      if (temp_data[x].value == input[i])
      {
        // Node found.
        temp_data[x].count++;
        found = true;
      }
    }
    if (temp_data.size() == 0 || !found)
    {
      // Create and assign node.
      temp_storage.value = input[i];
      temp_storage.count = 1;
      temp_data.push_back(temp_storage);
    }
  }

  int max_frequency=0;
  // Find highest frequency
  for (int x = 0; x < temp_data.size(); x++)
  {
    if (temp_data[x].count > max_frequency)
    {
      max_frequency = temp_data[x].count;
    }
  }

  // Add high frequency objects to the out going vector.
  for (int x = 0; x < temp_data.size(); x++)
  {
    if (temp_data[x].count == max_frequency)
    {
      output_data.push_back(temp_data[x].value);
    }
  }

  std::sort (output_data.begin(), output_data.end());

  return output_data;
}


#ifdef Debug
void debug_printf(std::vector<int> result)
{
  for (int x=0;x<result.size();x++)
  {
    printf ("loop: %d=%d\n",x ,result[x]);
  }
}

int main()
{
  int test1[] = {1,1,1,1,1,2};
  int test2[] = {1,1,1,2,2,2};
  int test3[] = {1,2,3,4,5,6};
  int test4[] = {1,1,2,2,3,3};

  debug_printf (findMode(test1, ARRAY_LENGTH (test1)));
  debug_printf (findMode(test1, ARRAY_LENGTH (test2)));
  debug_printf (findMode(test1, ARRAY_LENGTH (test3)));
  debug_printf (findMode(test1, ARRAY_LENGTH (test4)));
  return 0;
}
#endif
