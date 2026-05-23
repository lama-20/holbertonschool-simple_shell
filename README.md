# Simple Shell

A simple UNIX command line interpreter written in C

## Description

**hsh** is a simple UNIX shell that reads commands from the user or from a pipe, finds them using the PATH environment variable, and executes them using `execve`. It supports basic built-in commands, handles errors gracefully, and works in both interactive and non-interactive modes.

## Features

- Displays a prompt `($) ` in interactive mode
- Executes commands with arguments
- Searches for commands using the `PATH` environment variable
- Does **not** fork if the command does not exist
- Handles end-of-file (`Ctrl+D`)
- Built-in commands: `exit` and `env`
- Passes `environ` to all executed commands
- Prints descriptive error messages when a command is not found

## Files

| File | Description |
|------|-------------|
| `main.c` | Entry point — contains the main loop, input parsing, command execution, and built-in handling |
| `path.c` | Contains the `_which` function that searches for a command in the PATH |
| `shell.h` | Header file with all function prototypes, macros, and standard library includes |
| `man_1_simple_shell` | Manual page for the shell |
| `AUTHORS` | List of all contributors to the project |


## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

In interactive mode, the shell displays a prompt and waits for the user to type a command:

```bash
$ ./hsh
($) /bin/ls
hsh main.c path.c shell.h
($) ls -l /tmp
total 0
($) exit
$
```

### Non-Interactive Mode

In non-interactive mode, commands are passed through a pipe:

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c path.c shell.h
$
```

## Built-in Commands

| Command | Description |
|---------|-------------|
| `exit` | Exit the shell. Uses the exit status of the last executed command. |
| `env` | Print all current environment variables, one per line. |

## How It Works

When the user types a command, the shell follows these steps:

1. Reads the input line using `getline`
2. Parses the line into a command and its arguments using `strtok`
3. Checks if the command is a built-in (`exit` or `env`)
4. If not a built-in, searches for the command in the `PATH` using `_which`
5. If the command is found, forks a child process and calls `execve` to run it
6. If the command is **not** found, prints an error message and does **not** fork
7. Waits for the child process to finish and collects the exit status
8. Displays the prompt again

## Examples

```bash
($) ls
hsh main.c path.c shell.h

($) ls -l /tmp
total 20
drwx------ 3 root root 4096 May 23 12:09 systemd-private

($) /bin/echo Hello World
Hello World

($) env
USER=lama
HOME=/home/lama
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
...

($) exit
```

## Error Handling

If a command is not found, the shell prints an error in the following format:
./hsh: 1: ls: not found
