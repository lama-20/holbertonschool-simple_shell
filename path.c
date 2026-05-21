#include "shell.h"

char *_which(char *command)
{
    char *path = getenv("PATH"), *path_copy, *token, *full_path;
    struct stat st;

    if (command[0] == '/' || command[0] == '.')
    {
        if (stat(command, &st) == 0) return (strdup(command));
        return (NULL);
    }
    path_copy = strdup(path);
    token = strtok(path_copy, ":");
    full_path = malloc(1024);
    while (token)
    {
        sprintf(full_path, "%s/%s", token, command);
        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return (full_path);
        }
        token = strtok(NULL, ":");
    }
    free(path_copy);
    free(full_path);
    return (NULL);
}
