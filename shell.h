#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

char *_getenv(char *name);
char *_which(char *command);
void parse_line(char *line, char **argv);
int execute_cmd(char *full_cmd, char **argv, char **env);
void print_env(void);

#endif
