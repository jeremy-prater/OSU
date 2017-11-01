#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "smallsh-shell.h"
#include "smallsh-process.h"

static char inputBuffer[MAX_SHELL_INPUT];

int main(int argc, char * argv[])
{
    InitProcessManager();
    int running = 1;

    while (running)
    {
        GetInput(inputBuffer);
        struct parsedCommandLine currentCommand = ProcessCommand(inputBuffer);

        printf ("Processing command type [%d]\n", currentCommand.commandType);
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
                    printf ("Changing directory to [%s]\n", currentCommand.argv[1]);
                    if (chdir(currentCommand.argv[1]))
                    {
                        printf ("Failed to change directory to [%s] [%s]\n", currentCommand.argv[1], strerror(errno));
                    }

                }
                else
                {
                    printf ("cd: no directory specified\n");
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
                        printf ("system failure...\n");
                        exit (-1);
                    }
                    break;
                    case 0:
                    {
                        // This is the child. Execute the commands!
                        execvp (currentCommand.argv[0], &currentCommand.argv[1]);
                    }
                    break;
                    default:
                    {
                        // I'm the parent... Monitor the child process
                        AddProcess(spawnPID);
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