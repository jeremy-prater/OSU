#include <stdlib.h>
#include <time.h>

Dice::Dice ()
{
  Dice(6);
}

Dice::Dice (unsigned int newNumFaces)
{
  // Use value from constructor to setup number of faces
  this->numFaces = newNumFaces;
  // Seed rand with local system time.
  srand (mktime(localtime(0)));
}

unsigned int Dice::GetNumFaces()
{
  // Return the number of faces.
  return this->numFaces;
}
unsigned int Dice::Roll()
{
  // Return value from [1, GetNumFaces()]
  return 1 + (rand() % (this->GetNumFaces() - 1));
}

unsigned int LoadedDice::Roll()
{
  // Get value
  int result = Dice::Roll();
  // Check for 5 percent chance to be LoadedDice.
  if ((rand() % 100) >= 5)
  {
    // Increase result.
    result++;
    // Check if we are over max faces.
    if (result > this->GetNumFaces())
    {
      //Set result to max faces
      result = this->GetNumFaces();
    }
  }
  // Return result.
  return result;
}
