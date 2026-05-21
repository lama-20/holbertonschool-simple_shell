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
			free(full_cmd);
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}

/**
 * main - Entry point for the simple shell
 * @ac: Argument count
 * @av: Argument vector
 * Return: Always 0
 */
int main(int ac, char **av)
{
	char *line = NULL, *argv[64], *token, *full_cmd;
	size_t len = 0;
	int i, loop_count = 0;
	(void)ac;

	while (1)
	{
		loop_count++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		if (getline(&line, &len, stdin) == -1)
			break;
		i = 0;
		token = strtok(line, " \t\n");
		while (token && i < 63)
		{
			argv[i++] = token;
			token = strtok(NULL, " \t\n");
		}
		argv[i] = NULL;
		if (argv[0] == NULL)
			continue;
		if (strcmp(argv[0], "exit") == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		full_cmd = _which(argv[0]);
		if (full_cmd == NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", av[0], loop_count, argv[0]);
			continue;
		}
		exec_child(full_cmd, argv, line);
		free(full_cmd);
	}
	free(line);
	return (0);
}
