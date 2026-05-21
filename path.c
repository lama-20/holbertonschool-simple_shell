#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable
 * @name: Name of the variable to find
 * Return: Pointer to the value, or NULL if not found
 */
char *_getenv(char *name)
{
	int i = 0, j;

	if (!name || !environ)
		return (NULL);
	while (environ[i])
	{
		j = 0;
		while (name[j] && environ[i][j] == name[j])
			j++;
		if (name[j] == '\0' && environ[i][j] == '=')
			return (environ[i] + j + 1);
		i++;
	}
	return (NULL);
}

/**
 * _which - Finds the full path of a command
 * @command: Command to find
 * Return: Pointer to the full path, or NULL if not found
 */
char *_which(char *command)
{
	char *path, *p_copy, *token, *f_path;
	struct stat st;

	if (!command)
		return (NULL);
	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		return (NULL);
	}
	path = _getenv("PATH");
	if (!path || *path == '\0')
		return (NULL);
	p_copy = strdup(path);
	if (!p_copy)
		return (NULL);
	f_path = malloc(1024);
	if (!f_path)
	{
		free(p_copy);
		return (NULL);
	}
	token = strtok(p_copy, ":");
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
