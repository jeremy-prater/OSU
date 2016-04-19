/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 18, 2016
** Description:  Module 4.a assignment
*********************************************************************/

#include <iostream>
#include <cmath>

/*********************************************************************
** Description: Assignment 4.a
**
** Write a function called fallDistance that takes time as an
** argument and returns distance.
**
**
*********************************************************************/

/*********************************************************************
** Definitions
**
*********************************************************************/


/*********************************************************************
** float fallDistance (float time)
**
** Compute the distance fallen based on time
**
*********************************************************************/

float fallDistance (float time)
{
  return (1.0f/2)(9.8f)(pow(time,2));
}

#ifdef Debug
void main(void)
{
  cout << fallDistance (1.0f) << endl;
  cout << fallDistance (2.0f) << endl;
  cout << fallDistance (3.0f) << endl;
}
#endif
