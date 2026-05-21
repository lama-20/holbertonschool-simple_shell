char *full_cmd = _which(argv[0]);

if (full_cmd == NULL)
{
    perror("./hsh");
    continue;
}

pid = fork();
if (pid == 0)
{
    execve(full_cmd, argv, environ);
}
else
{
    wait(NULL);
    free(full_cmd);
}
