#include "main.h"

/**
 * main - Entry point
 *
 * Return: 0 Success
 */
int main(void)
{

    char *buff = NULL;
    size_t length = 0;
    ssize_t input;
    pid_t child_process;
    int status;
    char *argv[100];

    while (1)
    {
        printf("Shell$ ");
        input = getline(&buff, &length, stdin);

        if (input == -1)
        {
            printf("exit");
            return (-1);
        }

        format_input(argv, buff, "\n");

        child_process = fork();
        if (child_process == -1)
        {
            perror("Failed to create a child process");
            return (1);
        }

        if (child_process == 0)
        {
            _execute_command(argv, __environ);
        }
        else
        {
            waitpid(child_process, &status, 0);
        }
    }

    free(buff);
    return (0);
}