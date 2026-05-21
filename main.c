#include "shell.h"

/**
 * main - simple shell entry point
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL, *argv[2], *full_cmd;
	size_t len = 0;
	pid_t pid;

	while (getline(&line, &len, stdin) != -1)
	{
		line[strcspn(line, "\n")] = 0;
		argv[0] = line;
		argv[1] = NULL;
		full_cmd = _which(argv[0]);
		if (full_cmd == NULL)
		{
			perror("./hsh");
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			execve(full_cmd, argv, environ);
			exit(EXIT_FAILURE);
		}
		wait(NULL);
		free(full_cmd);
	}
	free(line);
	return (0);
}
