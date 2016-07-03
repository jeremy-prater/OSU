#include "dice.hpp"
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "lib_flip_display.hpp"

Dice::Dice ()
{
  this->Init(6);
}

Dice::Dice (unsigned int numNewFaces)
{
  this->Init (numNewFaces);
}

void Dice::Init (unsigned int newNumFaces)
{
  // Use value from constructor to setup number of faces
  this->numFaces = newNumFaces;
  // Seed rand with local system time.
  unsigned int randomSeed;

  int fd = open("/dev/urandom", O_RDONLY);
  read(fd, &randomSeed, sizeof (unsigned int));
  close(fd);
  srand(randomSeed); // IRL, check for errors, close the fd, etc...
  debug_print (false, COLOR_YELLOW, "Created Dice: Seed: %u, Faces: %u\n", randomSeed, this->numFaces);
}

unsigned int Dice::GetNumFaces() const
{
  // Return the number of faces.
  return this->numFaces;
}

unsigned int Dice::Roll() const
{
  // Return value from [1, GetNumFaces()]
  return 1 + (rand() % this->GetNumFaces());
}

LoadedDice::LoadedDice() : Dice()
{

}

LoadedDice::LoadedDice(unsigned int newNumFaces) : Dice(newNumFaces)
{

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
