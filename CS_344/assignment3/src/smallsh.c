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

int main(int argc, char * argv[])
{
    RegisterSignalHandlers();
    InitProcessManager();
    int running = 1;

    while (running)
    {
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
                    //printf ("Changing directory to [%s]\n", currentCommand.argv[1]);
                    if (chdir(currentCommand.argv[1]))
                    {
                        //printf ("Failed to change directory to [%s] [%s]\n", currentCommand.argv[1], strerror(errno));
                    }

                }
                else
                {
                    //printf ("cd: no directory specified\n");
                }
                fflush(stdout);
            }
            break;
            case SHELL_CMD_STATUS:
            {

            }
            break;
            case SHELL_CMD_EXTERNAL:
            {
                pid_t spawnPID = fork();
                switch (spawnPID)
                {
                    case -1:
                    {
                        //printf ("system failure... [%s]\n", strerror(errno));
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
                            if (dup2(inputFileFD, 0) == -1)
                            {
                                //printf ("inputFD dup2 failed [%s]\n", strerror(errno));
                                exit(errno);
                            }
                        }
                        else if (currentCommand.background)
                        {
                            // Redirect background input to /dev/null
                            //printf ("backgrounding stdin\n");
                            int inputFileFD = open ("/dev/null", O_RDONLY);
                            if (dup2(inputFileFD, 0) == -1)
                            {
                                //printf ("inputFD dup2 failed [%s]\n", strerror(errno));
                                exit(errno);
                            }
                        }

                        if (currentCommand.outputFile)
                        {
                            int outputFileFD = open (currentCommand.outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                            if (dup2(outputFileFD, 1) == -1)
                            {
                                //printf ("outputFD dup2 failed [%s]\n", strerror(errno));
                                exit(errno);
                            }
                        }
                        else if (currentCommand.background)
                        {
                            // Redirect background input to /dev/null
                            //printf ("backgrounding stdout\n");
                            int outputFileFD = open ("/dev/null", O_WRONLY);
                            if (dup2(outputFileFD, 1) == -1)
                            {
                                //printf ("inputFD dup2 failed [%s]\n", strerror(errno));
                                exit(errno);
                            }
                        }

                        // pipe - (input, output)
                        if (execvp (currentCommand.argv[0], &currentCommand.argv[0]) == -1)
                        {
                            //printf ("Command failed! [%s]\n", strerror(errno));
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
                        }
                    }
                    break;
                }    
            }
            break;
        }
        CleanupCommandLine(&currentCommand);

        // Check all child processes...
        // waitpid (pid_t pid, int  *exitmethod(), int options) // WNOHANG

        // if (WIFEXITED(childexitmethod) != 0)
        // process exit normally
        // int exitStatus = WEXITSTATUS (childexitmethod)

        // if (WIFSIGNALED(childexitmethod) != 0)
        // process exit by signal
        // int exitSignal = WTERMSIG (childexitmethod)


    }
}