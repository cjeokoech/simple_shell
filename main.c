#include "shell.h"

void _prompt(int signal);
int myexecve(char **ac, char **ptr);

/**
 * _prompt - Prints a new prompt upon a signal.
 * @s: The signal.
 */
void _prompt(int s)
{
	char *print_prompt = "\n$ ";

	(void)s;
	signal(SIGINT, _prompt);
	write(STDIN_FILENO, print_prompt, 3);
}

/**
 * myexecve - Executes a command in a child process.
 * @ac: An array of arguments.
 * @ptr: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int myexecve(char **ac, char **ptr)
{
	pid_t pid;
	int status, flag = 0, r = 0;
	char *command = ac[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = _locate(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			r = (myerror(ac, 126));
		else
			r = (myerror(ac, 127));
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (pid == 0)
		{
			execve(command, ac, environ);
			if (errno == EACCES)
				r = (myerror(ac, 126));
			_free_env();
			free_memory(ac, ptr);
			free_alias(aliases);
			_exit(r);
		}
		else
		{
			wait(&status);
			r = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (r);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int r = 0, n;
	int *exect = &n;
	char *prompt = "$ ", *new = "\n";

	name = argv[0];
	history_counter = 1;
	aliases = NULL;
	signal(SIGINT, _prompt);

	*exect = 0;
	environ = copy_env();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		r = run_command(argv[1], exect);
		_free_env();
		free_alias(aliases);
		return (*exect);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (r != END_OF_FILE && r != EXIT)
			r = handle_command(exect);
		_free_env();
		free_alias(aliases);
		return (*exect);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		r = handle_command(exect);
		if (r == END_OF_FILE || r == EXIT)
		{
			if (r == END_OF_FILE)
				write(STDOUT_FILENO, new, 1);
			_free_env();
			free_alias(aliases);
			exit(*exect);
		}
	}

	_free_env();
	free_alias(aliases);
	return (*exect);
}

