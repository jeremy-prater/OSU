#ifndef SMALLSH_SHELL_H
#define SMALLSH_SHELL_H

#define MAX_SHELL_INPUT 2048
#define MAX_SHELL_ARGS 512

int ProcessCommand(const char * input);
int GetInput(char * input);

#endif // SMALLSH_SHELL_H