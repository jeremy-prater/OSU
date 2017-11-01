#include "smallsh-shell.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void parseCommandLine(char * input, struct parsedCommandLine * commandLine)
{
    input = strtok(input, " ");
    commandLine->argc = 0;
    commandLine->argv = 0;
    while (input != 0)
    {
        commandLine->argv = (char **)realloc(commandLine->argv, sizeof (char *) * ++commandLine->argc);
        commandLine->argv[commandLine->argc - 1] = strdup(input);
        input = strtok(0, " ");
        char * stringTest = commandLine->argv[commandLine->argc - 1];
        if ((!input) && (stringTest[strlen(stringTest) - 1] == '\n'))
        {
            stringTest[strlen(stringTest) - 1] = 0x00;
        }
    }
    commandLine->argv = (char **)realloc(commandLine->argv, sizeof (char *) * ++commandLine->argc);
    commandLine->argv[commandLine->argc - 1] = malloc(1);
    commandLine->argv[commandLine->argc - 1][0] = 0x00;
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

    if ((input[0] == '#') || (input[0] == '\n'))
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
