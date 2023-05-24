#include "main.h"

/**
 * main - Entry point
 *
 * Return: 0 Success
 */
int main(__attribute__((unused))int argc, char *argv[], char *envp[])
{
	char *buff = NULL;
	size_t length = 0;
	ssize_t input;
	pid_t child_process;
	int status;
	char *args[100];

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		input = getline(&buff, &length, stdin);

		if (input == -1)
		{
			exit(EXIT_SUCCESS);
		}

		format_input(args, buff, "\n");

		child_process = fork();
		if (child_process == -1)
		{
			perror("Failed to create a child process\n");
			return (1);
		}

		if (child_process == 0)
		{
			_execute_command(args, envp, argv);
		}
		else
		{
			waitpid(child_process, &status, 0);
		}
	}

	free(buff);
	return (0);
}
