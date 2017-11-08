#include "smallsh-shell.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static void parseCommandLine(char * input, struct parsedCommandLine * commandLine)
{
    // Strip trailing eol off command line
    int strLen = strlen (input);
    input[strLen - 1] = 0x00;

    // Get initial command
    input = strtok(input, " ");
    commandLine->argc = 0;
    commandLine->argv = 0;
    commandLine->outputFile = 0;
    commandLine->inputFile = 0;
    commandLine->background = 0;

    unsigned char nextArgumentIsInputFile = 0;
    unsigned char nextArgumentIsOutputFile = 0;


    if (input != 0)
    {
        commandLine->argc++;
        commandLine->argv = (char **)realloc(commandLine->argv, sizeof (char *) * commandLine->argc);
        commandLine->argv[commandLine->argc - 1] = strdup(input);
        printf ("============= Command [%s]\n", commandLine->argv[commandLine->argc - 1]);
    }

    // Append command arguments
    input = strtok(0, " ");
    while (input != 0)
    {
        printf ("============= Token [%s]\n", input);
        if (strcmp(input, "<") == 0)
        {
            nextArgumentIsInputFile = 1;
        }
        else if (nextArgumentIsInputFile == 1)
        {
            nextArgumentIsInputFile = 0;
            commandLine->inputFile = strdup(input);
            printf ("============= Input File [%s]\n", commandLine->inputFile);
        }
        else if (strcmp(input, ">") == 0)
        {
            nextArgumentIsOutputFile = 1;
        }
        else if (nextArgumentIsOutputFile == 1)
        {
            nextArgumentIsOutputFile = 0;
            commandLine->outputFile = strdup(input);
            printf ("============= Output File [%s]\n", commandLine->outputFile);
        }
        else if (strcmp(input, "&") == 0)
        {
            commandLine->background = 1;
            printf ("============= backgrounding...\n");
        }
        else
        {
            commandLine->argv = (char **)realloc(commandLine->argv, sizeof (char *) * ++commandLine->argc);
            char * argument = strdup (input);
            char * pidExpand = strstr (argument, "$$");
            if (pidExpand)
            {
                char pidString[10];
                memset (pidString, 0, 10);
                pid_t pid = getpid();
                snprintf(pidString, 10, "%d", pid);
                int pidLength = strlen(pidString);
                int argumentLength = strlen (argument);

                int newArgSize = argumentLength + pidLength - 1;
                argument = (char*) realloc(argument, newArgSize);
                pidExpand = strstr (argument, "$$");
                if (argument + argumentLength > pidExpand + 2)
                {
                    // Extra text!
                    memmove (pidExpand + pidLength, pidExpand + 2 , strlen(pidExpand + 2));  
                }
                memcpy(pidExpand, pidString, pidLength);
                argument[newArgSize - 1] = 0x00;
            }
            commandLine->argv[commandLine->argc - 1] = strdup(argument);
            free(argument);
            printf ("============= Argument [%s]\n", commandLine->argv[commandLine->argc - 1]);
        }
        input = strtok(0, " ");
    }

    // Append trailing null on argv
    commandLine->argc++;
    commandLine->argv = (char **)realloc(commandLine->argv, sizeof (char *) * commandLine->argc);
    commandLine->argv[commandLine->argc - 1] = 0x00;
}

void CleanupCommandLine (struct parsedCommandLine * commandLine)
{
    int index = 0;
    for (index = 0; index < commandLine->argc; index++)
    {
        free (commandLine->argv[index]);
    }
    free (commandLine->argv);
}

struct parsedCommandLine ProcessCommand(char * input)
{
    struct parsedCommandLine commandLine;
    parseCommandLine(input, &commandLine);

    printf ("Processing command [%s] with arguments [%d]\n", commandLine.argv[0], commandLine.argc);

    if ((input[0] == '#') || (input[0] == '\n') || (!commandLine.argv[0]))
    {
        commandLine.commandType = SHELL_CMD_COMMENT;
    }
    else if (commandLine.argc > 0)
    {
        if (strcmp (commandLine.argv[0], "exit") == 0)
        {
            commandLine.commandType = SHELL_CMD_EXIT;
        }
        else if (strcmp (commandLine.argv[0], "cd") == 0)
        {
            commandLine.commandType = SHELL_CMD_CD;
        }
        else if (strcmp (commandLine.argv[0], "status") == 0)
        {
            commandLine.commandType = SHELL_CMD_STATUS;
        }
        else
        {
            commandLine.commandType = SHELL_CMD_EXTERNAL;
        }
    }

    return commandLine;
}

char * GetInput(char * input)
{
    printf (": ");
    fflush(stdin);
    return fgets(input, MAX_SHELL_INPUT, stdin);
}
