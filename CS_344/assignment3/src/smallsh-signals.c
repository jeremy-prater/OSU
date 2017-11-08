#include "smallsh-signals.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>

void signalSIGINT(int signo)
{
    printf ("\n\nSIGINT : Terminating child processes\n");
}    

void signalSIGSTP(int signo)
{
    printf ("\n\nSIGTSTP : party rock?\n");
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
