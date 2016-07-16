#include "transformer.hpp"

void Transformer::doFilter (ifstream &in, ofstream & out)
{
    // Read all ifstream
    // Call transformer
    // ofstream write
    char data;
    while (in.get(data))
    {
        out << transform (data);
    }
}

Transformer::Transformer()
{

}

Transformer::~Transformer()
{

}
