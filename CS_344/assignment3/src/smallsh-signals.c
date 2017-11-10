#include "smallsh-signals.h"
#include "smallsh.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>

void signalSIGINT(int signo)
{
    fprintf (stdout, "\n\nSIGINT : Terminating child foreground processes\n");
    fflush(stdout);
}    

void signalSIGSTP(int signo)
{
    ToggleForegroundOnly();
    if (GetToggleForegroundOnly())
    {
        fprintf (stdout, "\n\nSIGTSTP : Background proccess are disabled\n");
        fflush(stdout);
    }
    else
    {
        fprintf (stdout, "\n\nSIGTSTP : Background proccess are enabled\n");
        fflush(stdout);
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
