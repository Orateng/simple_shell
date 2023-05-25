#include "main.h"

/**
 * format_input - tokenize the input to not include a newline
 * @argv: arguments array
 * @buff: buffer which contains the input
 * @delim: the delimeter to use to separate the arguments
 */
void format_input(char **argv, char *buff, char *delim)
{
	int i;
	char *token = strtok(buff, delim);

	for (i = 0; token != NULL; i++)
	{
		argv[i] = token;
		token = strtok(NULL, delim);
	}
	argv[i] = NULL;
}
