#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#include "smallsh-process.h"
#include "smallsh.h"


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
    int exitedStatus;
    waitpid(processID, &exitedStatus, 0);
    if (WIFEXITED(exitedStatus) != 0)
    {
        int exitStatus = WEXITSTATUS(exitedStatus);
        SetStatus (0, processID, exitStatus);
        printf (" --- Processs [%d] exited [%d]\n", processID, exitStatus);
    }
    else if (WIFSIGNALED(exitedStatus) != 0)
    {
        int exitSignal = WTERMSIG(exitedStatus);
        printf (" --- Processs [%d] exited by signal [%d]\n", processID, exitSignal);
        SetStatus (1, processID, exitSignal);
        
    }
}