/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 24, 2016
** Description:  Lab Aa
*********************************************************************/
#include "summation.h"

/*********************************************************************
** Description: Lab Aa summation.cpp
**
** Implementation for summation.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// double sum (double * arrayPtr, unsigned int arrayLength)
//
// return the sum of an array of doubles.
//

double sum(double * arrayPtr, unsigned int arrayLength)
{
  // Declare a local double for the average.
  double arraySum = 0;

  for (unsigned int arrayPosition = 0; arrayPosition < arrayLength; arrayPosition++)
  {
    // Sum all the elements of arrayPtr
    arraySum += arrayPtr[arrayPosition];
  }
  
  // Return the result
  return arraySum;
}
