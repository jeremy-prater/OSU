#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "fileLoader.hpp"
#include <string.h>
#include "lib_flip_display.hpp"

fileLoader::fileLoader (std::string filename)
{
    dataBufferCapacity = 5;
    dataBufferCount = 0;
    dataBuffer = (int*)malloc (dataBufferCapacity * sizeof (int));
    fileName = filename;
    std::ifstream file (fileName);
    std::string data;
    while ( file.good() )
    {
        std::getline (file, data, ',' );
        data.erase(std::remove(data.begin(), data.end(), ' '), data.end());
        AddData (std::stoi(data));
    }
}

fileLoader::~fileLoader()
{
    free (dataBuffer);
}

void fileLoader::AddData (int data)
{
    dataBuffer[dataBufferCount++] = data;
    if (dataBufferCount == dataBufferCapacity)
    {
        dataBufferCapacity *= 2;
        dataBuffer = (int*)realloc (dataBuffer, dataBufferCapacity * sizeof (int));           
    }
}

int * fileLoader::GetBuffer()
{
    return dataBuffer;
}

void fileLoader::SaveData(std::string filename)
{
    DebugConsole::debug_print (0, true, COLOR_GREEN, "Saving data to  %s\n\n", filename.c_str());
    std::ofstream output (filename);
    fileName = filename;
    for (int index = 0; index < dataBufferCount; index++)
    {
        output << dataBuffer[index];
        if (index < dataBufferCount - 1)
        {
            output << ", ";
        }
    }        
}

void fileLoader::PrintData()
{
    DebugConsole::debug_print (0, true, COLOR_GREEN, "Printing values:\n\n");
    for (int index = 0; index < dataBufferCount; index++)
    {
        DebugConsole::debug_print (0, false, COLOR_WHITE, "%d: %d\n", index, dataBuffer[index]);
    }    
}

int fileLoader::LinearSearch(int value)
{
    DebugConsole::debug_print (0, true, COLOR_WHITE, "Preforming Linear Search.\n");
    for (int searchIndex = 0; searchIndex < dataBufferCount; searchIndex++)
    {
        if (dataBuffer[searchIndex] == value)
        {
            DebugConsole::debug_print (0, true, COLOR_GREEN, "%d was found at index %d in %s\n",value, searchIndex, fileName.c_str());
            return searchIndex;
        }
    }
    DebugConsole::debug_print (0, true, COLOR_YELLOW, "%d was not found in %s\n",value, fileName.c_str());
    return -1;
}

void fileLoader::BubbleSort()
{
    DebugConsole::debug_print (0, true, COLOR_WHITE, "Preforming Bubble Sort.\n");
    int tempStorage;
    bool sorting = true;
    do
    {
        sorting = false;
        for (int sortIndex = 0; sortIndex < dataBufferCount - 1; sortIndex++)
        {
            if (dataBuffer[sortIndex] > dataBuffer[sortIndex + 1])
            {
                tempStorage = dataBuffer[sortIndex];
                dataBuffer[sortIndex] = dataBuffer[sortIndex + 1];
                dataBuffer[sortIndex + 1] = tempStorage;
                sorting = true;
            }
        }
    } while(sorting);
}

int fileLoader::BinarySearch (int value)
{
    DebugConsole::debug_print (0, true, COLOR_WHITE, "Preforming Binary Search.\n");
    int firstIndex = 0;
    int lastIndex = dataBufferCount - 1;
    int middleIndex;
    int position = -1;
    bool foundValue = false;
    while (!foundValue && (firstIndex <= lastIndex))
    {
        middleIndex = (firstIndex + lastIndex) / 2;
        if (dataBuffer[middleIndex] == value)
        {
            foundValue = true;
            position = middleIndex;
            DebugConsole::debug_print (0, true, COLOR_GREEN, "%d was found at index %d in %s\n",value, position, fileName.c_str());
        }
        else if (dataBuffer[middleIndex] > value)
        {
            lastIndex = middleIndex - 1;
        }
        else
        {
            firstIndex = middleIndex + 1;
        }
    }
    if (position == -1)
    {
        DebugConsole::debug_print (0, true, COLOR_YELLOW, "%d was not found in %s\n",value, fileName.c_str());
    }
    return position;
}