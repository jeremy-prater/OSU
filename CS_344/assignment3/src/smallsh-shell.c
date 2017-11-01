#include "smallsh-shell.h"

#include <stdio.h>

int ProcessCommand(const char * input)
{
    printf ("Processing: %s\n", input);
}

char * GetInput(char * input)
{
    printf (": ");
    return fgets(input, MAX_SHELL_INPUT, stdin);
}
