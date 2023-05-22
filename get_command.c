#include "main.h"

char *get_location(const char *command)
{
    char *path = getenv("PATH");
    const char *delim = ":";
    char *path_token, *file_path;

    struct stat buffer;

    if (path == NULL)
    {
        return (NULL);
    }

    char *path_copy = strdup(path);

    if (path_copy == NULL)
    {
        perror("Memory allocation error");
        return (NULL);
    }

    path_token = strtok(path_copy, delim);
    file_path = malloc(strlen(command) + 2);

    if (file_path == NULL)
    {
        perror("Memory allocation error");
        free(path_copy);
        return (NULL);
    }

    while (path_token != NULL)
    {
        sprintf(file_path, "%s/%s", path_token, command);

        if (stat(file_path, &buffer) == 0)
        {
            free(path_copy);
            return (file_path);
        }
        path_token = strtok(NULL, delim);
    }

    free(file_path);
    free(path_copy);

    return (NULL);
}
