/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 24, 2016
** Description:  Lab Aa
*********************************************************************/
#include "average.h"

/*********************************************************************
** Description: Lab Aa average.cpp
**
** Implementation for average.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// double avg (double * arrayPtr, unsigned int arrayLength)
//
// return the average of an array of doubles.
//

double avg(double * arrayPtr, unsigned int arrayLength)
{
  // Declare a local double for the average.
  double arrayAvg = 0;

  if (arrayLength == 0)
  {
    // If the length is 0, return the default value of 0;
    return arrayAvg;
  }
  
  // Get the summation of the array and divide by length to get the average;
  arrayAvg = sum (arrayPtr, arrayLength) / arrayLength;

  // Return the result
  return arrayAvg;
}
