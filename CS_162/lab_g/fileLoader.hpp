#ifndef FILE_LOADER_HPP
#define FILE_LOADER_HPP

#include <string>

class fileLoader
{
private:
    std::string fileName;
    int * dataBuffer;
    int dataBufferCapacity;
    int dataBufferCount;
    void AddData(int data);

public:
    fileLoader (std::string filename);
    ~fileLoader();

    int * GetBuffer();
    void SaveData(std::string filename);
    void PrintData();
    int LinearSearch(int value);
    void BubbleSort();
    int BinarySearch(int value);
};

#endif /// FILE_LOADER_HPP