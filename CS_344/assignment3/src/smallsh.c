#include <stdio.h>
#include "smallsh-shell.h"

static char inputBuffer[MAX_SHELL_INPUT];

int main(int argc, char * argv[])
{
    int running = 1;

    while (running)
    {
        GetInput(inputBuffer);
        ProcessCommand(inputBuffer);
    }
}