#include "main.h"

/**
 * _execute_command - function to execute the program
 * @argv: arguments array
 * @args: argumets arry
 * @envp: environment variables array
 * Return: Void
 */
void _execute_command(char *args[], char *envp[], char **argv)
{
	if (execve(args[0], args, envp) == -1)
	{
		perror(argv[0]);
		exit(EXIT_FAILURE);
	}
}
