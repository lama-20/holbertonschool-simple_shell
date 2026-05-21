#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;
char *_which(char *command);
int _strcmp(char *s1, char *s2);

#endif
