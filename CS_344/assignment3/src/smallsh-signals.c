#include "smallsh-signals.h"
#include "smallsh.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>

void signalSIGINT(int signo)
{
    //printf ("\n\nSIGINT : Terminating child foreground processes\n");
}    

void signalSIGSTP(int signo)
{
    ToggleForegroundOnly();
    if (GetToggleForegroundOnly())
    {
        //printf ("\n\nSIGTSTP : Background proccess are disabled\n");
    }
    else
    {
        //printf ("\n\nSIGTSTP : Background proccess are enabled\n");
    }
}

void RegisterSignalHandlers()
{
    struct sigaction handler;
    memset (&handler, 0, sizeof (struct sigaction));

    handler.sa_handler = signalSIGINT;
    sigfillset(&handler.sa_mask);
    handler.sa_flags = 0;
    sigaction (SIGINT, &handler, NULL);

    handler.sa_handler = signalSIGSTP;
    sigfillset(&handler.sa_mask);
    handler.sa_flags = 0;
    sigaction (SIGTSTP, &handler, NULL);
}
