#include "shell.h"

/**
 * exec_child - Forks and executes a command
 * @full_cmd: Full path of the command
 * @argv: Arguments array
 * @line: Input line buffer to free on failure
 */
void exec_child(char *full_cmd, char **argv, char *line)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(full_cmd, argv, environ) == -1)
		{
			perror("./hsh");
			free(full_cmd);
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
		free(full_cmd);
	}
}

/**
 * main - Entry point for the simple shell
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL, *argv[64], *token, *full_cmd;
	size_t len = 0;
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		if (getline(&line, &len, stdin) == -1)
			break;
		i = 0;
		token = strtok(line, " \t\n");
		while (token)
		{
			argv[i++] = token;
			token = strtok(NULL, " \t\n");
		}
		argv[i] = NULL;
		if (argv[0] == NULL)
			continue;
		full_cmd = _which(argv[0]);
		if (full_cmd == NULL)
		{
			perror("./hsh");
			continue;
		}
		exec_child(full_cmd, argv, line);
	}
	free(line);
	return (0);
}
