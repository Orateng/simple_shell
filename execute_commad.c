#include "main.h"

/**
 * _execute_command - function to execute the program
 * @argv: arguments array
 * @envp: environment variables array
 * Return: Void
 */
void _execute_command(char *argv[], char *envp[])
{
    if (execve(argv[0], argv, envp) == -1)
    {
        perror("./simple_shell");
        exit(EXIT_FAILURE);
    }
}