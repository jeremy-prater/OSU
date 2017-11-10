#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "smallsh-shell.h"
#include "smallsh-process.h"
#include "smallsh-signals.h"

static char inputBuffer[MAX_SHELL_INPUT];
static int foregroundOnly = 0;

static int statusWasSignal = 0;
static int statusProcessID = 0;
static int statusExitValue = 0;

void ToggleForegroundOnly()
{
    foregroundOnly = !foregroundOnly;
}

int GetToggleForegroundOnly()
{
    return foregroundOnly;
}

void SetStatus (int wasSignal, int processID, int exitValue)
{
    statusWasSignal = wasSignal;
    statusProcessID = processID;
    statusExitValue = exitValue;
}

int main(int argc, char * argv[])
{
    RegisterSignalHandlers();
    InitProcessManager();
    int running = 1;

    while (running)
    {
        memset (inputBuffer, 0, sizeof (inputBuffer));
        // Check all backgrounded processes for termination.
        CheckBackgroundProcesses();

        GetInput(inputBuffer);
        struct parsedCommandLine currentCommand = ProcessCommand(inputBuffer);

        //printf ("Processing command type [%d]\n", currentCommand.commandType);
        switch (currentCommand.commandType)
        {
            case SHELL_CMD_EXIT:
            {
                running = 0;
            }
            break;
            case SHELL_CMD_CD:
            {
                if (currentCommand.argc > 2)
                {
                    fprintf (stdout, "Changing directory to [%s]\n", currentCommand.argv[1]);
                    if (chdir(currentCommand.argv[1]))
                    {
                        fprintf (stdout, "Failed to change directory to [%s] [%s]\n", currentCommand.argv[1], strerror(errno));
                    }
                }
                else
                {
                    fprintf (stdout, "cd: no directory specified\n");
                }
                fflush(stdout);
            }
            break;
            case SHELL_CMD_STATUS:
            {
                if (statusWasSignal)
                {
                    fprintf (stdout, "Process [%d] exited with signal [%d]\n", statusProcessID, statusExitValue);
                }
                else
                {
                    fprintf (stdout, "Process [%d] exited with status [%d]\n", statusProcessID, statusExitValue);
                }
                fflush (stdout);

            }
            break;
            case SHELL_CMD_EXTERNAL:
            {
                currentCommand.background &= !GetToggleForegroundOnly();
                pid_t spawnPID = fork();
                switch (spawnPID)
                {
                    case -1:
                    {
                        fprintf (stdout, "system failure... [%s]\n", strerror(errno));
                        fflush (stdout);
                        exit (-1);
                    }
                    break;
                    case 0:
                    {
                        // This is the child. Execute the commands!
                        char ** tmpdbg = &currentCommand.argv[0];
                        while (*tmpdbg != 0)
                        {
                            //printf ("child... args... [%s]\n", *tmpdbg);
                            tmpdbg++;
                        }
                        if (currentCommand.inputFile)
                        {
                            int inputFileFD = open (currentCommand.inputFile, O_RDONLY);
                            if (inputFileFD < 0)
                            {
                                fprintf (stdout, "Failed to open [%s] [%s]\n", currentCommand.inputFile, strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }
                            if (dup2(inputFileFD, 0) == -1)
                            {
                                fprintf (stdout, "inputFD dup2 failed [%s]\n", strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }
                        }
                        else if (currentCommand.background)
                        {
                            // Redirect background input to /dev/null
                            int inputFileFD = open ("/dev/null", O_RDONLY);
                            if (inputFileFD < 0)
                            {
                                fprintf (stdout, "Failed to open [/dev/null] [%s]\n", strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }
                            if (dup2(inputFileFD, 0) == -1)
                            {
                                fprintf (stdout, "inputFD dup2 failed [%s]\n", strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }
                        }

                        if (currentCommand.outputFile)
                        {
                            int outputFileFD = open (currentCommand.outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                            if (outputFileFD < 0)
                            {
                                fprintf (stdout, "Failed to open [%s] [%s]\n", currentCommand.outputFile, strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }

                            if (dup2(outputFileFD, 1) == -1)
                            {
                                fprintf (stdout, "outputFD dup2 failed [%s]\n", strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }
                        }
                        else if (currentCommand.background)
                        {
                            // Redirect background input to /dev/null
                            int outputFileFD = open ("/dev/null", O_WRONLY);
                            if (outputFileFD < 0)
                            {
                                fprintf (stdout, "Failed to open [/dev/null] [%s]\n", strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }

                            if (dup2(outputFileFD, 1) == -1)
                            {
                                fprintf (stdout, "inputFD dup2 failed [%s]\n", strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }
                        }

                        if (execvp (currentCommand.argv[0], &currentCommand.argv[0]) == -1)
                        {
                            fprintf (stdout, "Command failed! [%s]\n", strerror(errno));
                            fflush(stdout);
                            exit (errno);
                        }
                    }
                    break;
                    default:
                    {
                        // I'm the parent... Monitor the child process
                        //printf ("parent... [%d]\n", spawnPID);
                        if (!currentCommand.background)
                        {
                            WaitProcess(spawnPID);
                        }
                        else
                        {
                            AddProcess(spawnPID);
                            fprintf (stdout, " --> [%s] is running as background pid [%d]\n", currentCommand.argv[0], spawnPID);
                            fflush (stdout);
                        }
                    }
                    break;
                }
            }
            break;
        }
        CleanupCommandLine(&currentCommand);
    }
}