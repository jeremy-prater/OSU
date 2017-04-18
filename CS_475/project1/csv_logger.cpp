////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - CSV Logger
//
// Jeremy Prater
//

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "csv_logger.hpp"


FILE * CSVLogger::logFilePtr;

void CSVLogger::WriteLog(const char * format, ...)
{
    va_list list;
    va_start (list, format);
    vfprintf (CSVLogger::logFilePtr, format, list);
    va_end (list);
    fprintf (CSVLogger::logFilePtr, "\n");
    fflush (CSVLogger::logFilePtr);
}

bool CSVLogger::OpenLogFile(const char * logName)
{
    if (access (logName, R_OK) == 0)
    {
        // File exists, open as write-append
        CSVLogger::logFilePtr = fdopen (logName, "a");
    }
    else
    {
        // File does not, exist. Create and return new handle.
        CSVLogger::logFilePtr = creat (logName, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
    }
}

void CSVLogger::CloseLogFile()
{
    fclose (CSVLogger::logFilePtr);
}