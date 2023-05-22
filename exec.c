#include "main.h"

void execmd(char **argv)
{
	pid_t pid;
	int status, exitstatus = 0;
	char *command = argv[0];
	char *bin_path = get_location(command);

	if (bin_path == NULL)
	{
		fprintf(stderr, "Command not found: %s\n", command);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(bin_path, argv, __environ) == -1)
		{
			perror("Error executing command");
			exit(1);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			exitstatus = WEXITSTATUS(status);
		}
	}

	free(bin_path);
}