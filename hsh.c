#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int is_empty(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void trim_newline(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			return;
		}
		i++;
	}
}

char **split_line(char *line)
{
	int i = 0;
	char **tokens = malloc(sizeof(char *) * 64);
	char *token;

	if (!tokens)
		return (NULL);

	token = strtok(line, " \t");
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, " \t");
	}
	tokens[i] = NULL;
	return (tokens);
}

int main(void)
{
	char *line = NULL;
	char **argv;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("#cisfun$ ");
			fflush(stdout);
		}

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			exit(0);
		}

		trim_newline(line);

		if (is_empty(line))
			continue;

		argv = split_line(line);
		if (!argv)
			continue;

		pid = fork();
		if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				perror("./hsh");
				free(argv);
				exit(1);
			}
		}
		else
		{
			wait(NULL);
		}
		free(argv);
	}

	free(line);
	return (0);
}
