
class Transformer
{
public:
    void doFilter (ifstream &in, ofstream & out);
    Transformer();
    ~Transformer();

protected:
    virtual char transform (char ch) = 0;
}

class Copy : public Transformer
{
public:
    Copy();
    ~Copy();

protected:
    virtual char transform (char ch);
}

class Encryption : public Transformer
{
public:
    Encryption(int keyToUse);
    ~Encryption();
private:
    int encryptionKey;

protected:
    virtual char transform (char ch);
}

class ToUpper : public Transformer
{
public:
    ToUpper();
    ~ToUpper();

protected:
    virtual char transform (char ch);
}

class OrderedOutput : public Transformer
{
public:
    OrderedOutput();
    ~OrderedOutput();

protected:
    virtual char transform (char ch);
}
