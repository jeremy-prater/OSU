#include "transformer.hpp"

void Transformer::doFilter (std::ifstream &in, std::ofstream & out)
{
    // Read all ifstream
    // Call transformer
    // ofstream write
    char data;
    while (in.get(data))
    {
        out << transform (data);
    }
    in.clear();
    in.seekg (0, std::ios::beg);
}

Transformer::Transformer()
{

}

Transformer::~Transformer()
{

}
