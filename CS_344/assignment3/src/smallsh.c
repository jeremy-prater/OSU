#include <stdio.h>
#include <unistd.h>
#include "smallsh-shell.h"
#include <errno.h>
#include <string.h>

static char inputBuffer[MAX_SHELL_INPUT];

int main(int argc, char * argv[])
{
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
                if (currentCommand.argc > 1)
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

            }
            break;
        }
        CleanupCommandLine(&currentCommand);
    }
}