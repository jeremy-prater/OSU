////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 325 - Homework 1
//
// Jeremy Prater
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "CSVLogger.hpp"
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>

#include "minChange.h"

static const char * dataLog = "./../hw3.csv";
static const char * dataSchema = "NUM_C,A,RUNTIME_CHANGE";

static struct timespec time0;
static struct timespec time1;

int main( int argc, char *argv[ ] )
{
    if (CSVLogger::OpenLogFile(dataLog))
    {
        CSVLogger::WriteLog(dataSchema);
    }

    // Read data from file
    // Open file
    std::ifstream fileStream ("./../data/amount.txt", std::ifstream::binary);

    std::string line;
    std::vector<coinSet_t> fileData;
    bool readMode = true;
    coinSet_t newSet;
    while (getline(fileStream, line))
    {
        if (readMode)
        {
            std::istringstream is(line);
            newSet.C = std::vector<int>(std::istream_iterator<int>(is), std::istream_iterator<int>());
        }
        else
        {
            newSet.A = stoi (line);
            fileData.push_back(newSet);
        }
        readMode = !readMode;          
    }
    uint32_t loadedSets = fileData.size();
    printf ("-> Loaded Sets : %d\n", loadedSets);
    for (uint32_t currentSet = 0; currentSet < loadedSets; currentSet++)
    {
        WriteMinCoins (&fileData[currentSet], "./../change.txt");
    }
    printf ("-> Processed Sets : %d\n", loadedSets);

    CSVLogger::CloseLogFile();
}
