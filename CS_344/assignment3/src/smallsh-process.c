#include <stdlib.h>

#include "smallsh-process.h"


static pid_t * pidList;

static int processCount = 0;

void InitProcessManager()
{
    pidList = 0;
}

void AddProcess (pid_t processID)
{
    pidList = realloc(pidList, sizeof (pid_t) * ++processCount);
    pidList[processCount - 1] = processID;
}

void KillProcess (pid_t processID)
{

}

void WaitProcess (pid_t processID)
{

}