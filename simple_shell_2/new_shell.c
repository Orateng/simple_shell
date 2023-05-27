#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>

#define BUFFER_SIZE 1024

int main(void) {
    char command[BUFFER_SIZE];
    char *args[BUFFER_SIZE];
    int status;

    while (1) 
    {
	    if (isatty(STDIN_FILENO) != 0)
		    write(STDOUT_FILENO, "simple_shell$ ", 14);
        ssize_t bytesRead = read(STDIN_FILENO, command, BUFFER_SIZE);

        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
	else if (bytesRead == 0)
		break;

        // Remove newline character
        if (command[bytesRead - 1] == '\n') {
            command[bytesRead - 1] = '\0';
        } else {
            command[bytesRead] = '\0';
        }

        if (strcmp(command, "exit") == 0) {
            break;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            char *token = strtok(command, " ");
            int i = 0;

            while (token != NULL && i < BUFFER_SIZE - 1) {
                args[i] = token;
                token = strtok(NULL, " ");
                i++;
            }

            args[i] = NULL;

            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }

    return EXIT_SUCCESS;
}

