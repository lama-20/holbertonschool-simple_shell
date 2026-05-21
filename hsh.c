#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
	char *line = NULL, *argv[64], *token;
	size_t len = 0;
	int i;
	pid_t pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		if (getline(&line, &len, stdin) == -1)
			break;
		i = 0;
		token = strtok(line, " \t\n");
		while (token != NULL)
		{
			argv[i++] = token;
			token = strtok(NULL, " \t\n");
		}
		argv[i] = NULL;
		if (argv[0] == NULL)
			continue;
		pid = fork();
		if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
				perror("./hsh");
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
	}
	free(line);
	return (0);
}
