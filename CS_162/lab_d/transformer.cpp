#include "transformer.hpp"


void Transformer::doFilter (std::ifstream &in, std::ofstream & out)
{
    // Read all ifstream
    char data;
    while (in.get(data))
    {
        // Call transformer
        // ofstream write
        out << transform (data);
    }

    // Reset stream for next filter
    in.clear();
    in.seekg (0, std::ios::beg);
}
