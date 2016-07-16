#include "transformer.hpp"

char Encryption::transform (char ch)
{
    int outputCharacter = encryptionKey + ch;
    return (char)(outputCharacter % 26);
}

Encryption::Encryption (int keyToUse)  : Transformer()
{
    encryptionKey = keyToUse;
}

Encryption::~Encryption()
{

}
