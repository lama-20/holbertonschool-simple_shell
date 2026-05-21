#include "shell.h"

/**
 * main - Entry point for the simple shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, or last exit status
 */
int main(int ac, char **av)
{
	char *line = NULL, *argv[64], *token, *full_cmd;
	size_t len = 0;
	ssize_t nread;
	int i, status = 0, line_count = 0;
	pid_t pid;
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

		i = 0;
		token = strtok(line, " \t");
		while (token && i < 63)
		{
			argv[i++] = token;
			token = strtok(NULL, " \t");
		}
		argv[i] = NULL;

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

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(full_cmd);
			free(line);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execve(full_cmd, argv, environ) == -1)
			{
				perror(av[0]);
				free(full_cmd);
				free(line);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
		}
		free(full_cmd);
	}
	free(line);
	return (status);
}
