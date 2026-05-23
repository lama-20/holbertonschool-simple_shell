#include "shell.h"

/**
 * parse_line - Splits a line into tokens (arguments)
 * @line: The input string to parse
 * @argv: Array to store the tokens
 */
void parse_line(char *line, char **argv)
{
	int i = 0;
	char *token;

	token = strtok(line, " \t");
	while (token && i < 63)
	{
		argv[i++] = token;
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;
}

/**
 * execute_cmd - Forks and executes a command
 * @full_cmd: Full path of the command
 * @argv: Arguments array
 * @env: Environment variables
 * Return: Exit status of the executed command
 */
int execute_cmd(char *full_cmd, char **argv, char **env)
{
	pid_t pid;
	int status = 0;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		if (execve(full_cmd, argv, env) == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return (status);
}

/**
 * main - Entry point for the simple shell
 * @ac: Argument count
 * @av: Argument vector
 * Return: Last exit status
 */
int main(int ac, char **av)
{
	char *line = NULL, *argv[64], *full_cmd;
	size_t len = 0;
	ssize_t nread;
	int status = 0, line_count = 0;

	(void)ac;
	while (1)
	{
		line_count++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		parse_line(line, argv);
		if (argv[0] == NULL)
			continue;
		if (strcmp(argv[0], "exit") == 0)
		{
			free(line);
			exit(status);
		}
		full_cmd = _which(argv[0]);
		if (!full_cmd)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", av[0], line_count, argv[0]);
			status = 127;
			continue;
		}
		status = execute_cmd(full_cmd, argv, environ);
		free(full_cmd);
	}
	free(line);
	return (status);
}
