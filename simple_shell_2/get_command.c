#include "main.h"

/**
 * get_command - get the command paths using the
 * PATH variable
 * @argv: arguments
 * Return: int (Status)
 */
char *get_command(char *argv[])
{
	struct stat st;
	char *path = getenv("PATH");
	char *fullpath, *token;
	size_t token_len, args_len;

	token = strtok(path, ":");
	args_len = strlen(argv[0]);

	while (token)
	{
		token_len = strlen(token);
		fullpath = malloc(token_len + args_len + 2);

		if (fullpath == NULL)
		{
			perror("Error with malloc");
			return (NULL);
		}

		strcpy(fullpath, token);
		strcat(fullpath, "/");
		strcat(fullpath, argv[0]);

		if (stat(fullpath, &st) == 0)
		{
			char *command = fullpath;
			return (command);
		}
		free(fullpath);
		token = strtok(NULL, ":");
	}

	return (NULL);
}
