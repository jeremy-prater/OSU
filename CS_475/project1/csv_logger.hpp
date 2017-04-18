////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - CSV Logger
//
// Jeremy Prater
//

class CSVLogger
{
public:
    void WriteLog(const char * format, ...);

    static FILE * logFilePtr;
    static bool OpenLogFile(const char * logName);
    static void CloseLogFile();
};
