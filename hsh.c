#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * is_empty - checks if input is only spaces/tabs/newlines
 * @str: input string
 *
 * Return: 1 if empty, 0 otherwise
 */
int is_empty(char *str)
{
        int i = 0;

        if (!str)
                return (1);

        while (str[i])
        {
                if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
                        return (0);
                i++;
        }
        return (1);
}

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
                if (isatty(STDIN_FILENO))
                {
                        printf("#cisfun$ ");
                        fflush(stdout);
                }

                read = getline(&line, &len, stdin);

                if (read == -1)
                {
                        free(line);
                        exit(0);
                }

                if (read > 0 && line[read - 1] == '\n')
                        line[read - 1] = '\0';

                if (is_empty(line))
                        continue;

                args[0] = line;

                pid = fork();

                if (pid == 0)
                {
                        if (execve(args[0], args, NULL) == -1)
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
