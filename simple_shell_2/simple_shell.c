#include "main.h"

/**
 * main - Entry point
 * @argc: argument counter
 * @argv: argument vector
 * @envp: environment variables array
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
	char *args[100], *command;

	while (1)
	{
		if (isatty(STDIN_FILENO) != 0)
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		input = getline(&buff, &length, stdin);

		if (input == -1)
		{
			free(buff);
			exit(EXIT_SUCCESS);
		}
		if (buff[input] == '\n')
			buff[input] = '\0';

		format_input(args, buff, " \n");
		command = get_command(args);

		if (command != NULL)
			args[0] = command;

		child_process = fork();
		if (child_process == -1)
		{
			perror("Failed to create a child process\n");
			return (1);
		}

		if (child_process == 0)
		{
			printf("%s - %s\n", args[0], args[1]);
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
