#include "transformer.hpp"
#include "toupper.hpp"

char ToUpper::transform (char ch)
{
    // If ch is a lower case, change it to a upper case.
    if ((ch >= LOWER_A) && (ch <= LOWER_Z))
    {
        ch -= LOWER_TO_UPPER_OFFSET;
    }
    return ch;
}

ToUpper::ToUpper () : Transformer()
{

}

ToUpper::~ToUpper()
{

}
