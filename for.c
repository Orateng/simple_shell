#include "main.h"

#define LINESIZE 1024

int main(int argc, char **argv)
{
	char line[LINESIZE];
	char *buff = NULL;
	size_t length = 0;
	ssize_t input;
	const char *delim = " \n";
	char *token;
	int i;

	while (1)
	{
		printf("Shell$ ");
		input = getline(&buff, &length, stdin);

		if (input == -1)
		{
			free(buff);
			if (isatty(STDIN_FILENO) != 0)
				write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}
		else
		{
			char *p = strchr(buff, '\n');

			if (p)
				*p = '\0';
			if (strcmp(buff, "exit") == 0)
			{
				free(buff);
				exit(EXIT_SUCCESS);
			}
		}

		char *input_copy = strdup(buff);

		if (input_copy == NULL)
		{
			perror("Error with input");
			return (-1);
		}

		token = strtok(buff, delim);

		int token_no = 0;

		while (token != NULL)
		{
			token_no++;
			token = strtok(NULL, delim);
		}

		token_no++;

		char **arguments = malloc(sizeof(char *) * token_no);

		if (arguments == NULL)
		{
			perror("Error allocating memory");
			free(input_copy);
			return (-1);
		}

		token = strtok(input_copy, delim);

		for (i = 0; token != NULL; i++)
		{
			arguments[i] = strdup(token);
			token = strtok(NULL, delim);
		}
		arguments[i] = NULL;

		execmd(arguments);

		for (i = 0; i < token_no; i++)
			free(arguments[i]);
		free(arguments);
		free(input_copy);
	}

	return (0);
}
