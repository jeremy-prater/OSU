#include "transformer.hpp"
#include "toupper.hpp"

char ToUpper::transform (char ch)
{
    // Use key here to change ch...
    if ((ch >= LOWER_A) && (ch <= LOWER_Z))
    {
        ch -= LOWER_UPPER_OFFSET;
    }
    return ch;
}

ToUpper::ToUpper ()
{

}

ToUpper::~ToUpper()
{

}
