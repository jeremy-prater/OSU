#include "transformer.hpp"
#include "toupper.hpp"

void OrderedOutput::doFilter (std::ifstream &in, std::ofstream & out)
{
    int characterCounter = 0;
    char data;
    while (in.get(data))
    {
        if ((data != '\n') && (data != '\r') && (data != ' '))
        {
            out << transform (data);
            characterCounter++;
            if (characterCounter == 5)
            {
                characterCounter = 0;
                out << " ";
            }
        }
    }
    in.clear();
    in.seekg (0, std::ios::beg);
}

char OrderedOutput::transform (char ch)
{
    // If ch is a lower case, change it to a upper case.
    if ((ch >= LOWER_A) && (ch <= LOWER_Z))
    {
        ch -= LOWER_TO_UPPER_OFFSET;
    }
    return ch;
}

OrderedOutput::OrderedOutput () : Transformer()
{

}

OrderedOutput::~OrderedOutput()
{

}
