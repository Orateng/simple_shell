#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

void _execute_command(char *argv[], char *envp[], char **args);
void format_input(char **argv, char *buff, char *delim);
char *get_command(char *argv[]);

#endif
