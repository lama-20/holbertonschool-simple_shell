#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	char *args[] = {NULL, NULL};

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			printf("\n");
			free(line);
			exit(0);
		}

		line[read - 1] = '\0';
		args[0] = line;

		pid = fork();

		if (pid == 0)
		{
			execve(args[0], args, NULL);
			perror("./shell");
			exit(1);
		}
		else
		{
			wait(NULL);
		}
	}

	return (0);
}
