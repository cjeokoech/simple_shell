#include "shell.h"

void print_env(void);
void print_setenv(void);
void print_unsetenv(void);
void print_history(void);

/**
 * print_env - Displays information on the shell builtin command 'env'.
 */
void print_env(void)
{
	char *message = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, message, mystrlen(message));
}

/**
 * print_setenv - Displays information on the shell builtin command 'setenv'.
 */
void print_setenv(void)
{
	char *message = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, message, mystrlen(message));
	message = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, message, mystrlen(message));
}

/**
 * print_unsetenv - Displays information on the shell builtin command
 * 'unsetenv'.
 */
void print_unsetenv(void)
{
	char *message = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, message, mystrlen(message));
	message = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "message to stderr.\n";
	write(STDOUT_FILENO, message, mystrlen(message));
}

