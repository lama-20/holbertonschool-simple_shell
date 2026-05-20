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

char *trim_spaces(char *str)
{
	int end;

	while (*str == ' ' || *str == '\t')
		str++;

	end = strlen(str) - 1;
	while (end > 0 && (str[end] == ' ' || str[end] == '\t'))
	{
		str[end] = '\0';
		end--;
	}
	return (str);
}

int main(void)
{
	char *line = NULL;
	char *cmd;
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

		cmd = trim_spaces(line);

		pid = fork();
		if (pid == 0)
		{
			char *argv[2];

			argv[0] = cmd;
			argv[1] = NULL;
			if (execve(cmd, argv, environ) == -1)
			{
				perror("./hsh");
				exit(1);
			}
		}
		else
		{
			wait(NULL);
		}
	}

	free(line);
	return (0);
}
