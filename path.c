#include "shell.h"

/**
 * _which - finds the full path of a command
 * @command: command to find
 * Return: pointer to the full path, or NULL if not found
 */
char *_which(char *command)
{
	char *path = getenv("PATH"), *p_copy, *token, *f_path;
	struct stat st;

	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		return (NULL);
	}
	if (!path)
		return (NULL);
	p_copy = strdup(path);
	token = strtok(p_copy, ":");
	f_path = malloc(1024);
	while (token)
	{
		sprintf(f_path, "%s/%s", token, command);
		if (stat(f_path, &st) == 0)
		{
			free(p_copy);
			return (f_path);
		}
		token = strtok(NULL, ":");
	}
	free(p_copy);
	free(f_path);
	return (NULL);
}
