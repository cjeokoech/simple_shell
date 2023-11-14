#include "shell.h"

char *env_error(char **ac);
char *_error(char **ac);
char *_exit_error(char **ac);
char *directory_error(char **ac);
char *mysyntax(char **ac);
/**
 * _env_error - Creates an error message for myenv errors.
 * @ac: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *_env_error(char **ac)
{
	char *e, *history_str;
	int l;

	history_str = myitoa(history_counter);
	if (!history_str)
		return (NULL);

	ac--;
	l = mystrlen(name) + mystrlen(history_str) + mystrlen(ac[0]) + 45;
	e = malloc(sizeof(char) * (l + 1));
	if (!e)
	{
		free(history_str);
		return (NULL);
	}

	mystrcpy(e, name);
	mystrcat(e, ": ");
	mystrcat(e, history_str);
	mystrcat(e, ": ");
	mystrcat(e, ac[0]);
	mystrcat(e, ": Unable to add/remove from environment\n");

	free(history_str);
	return (e);
}

/**
 * _error - Creates an error message for _alias errors.
 * @ac: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *_error(char **ac)
{
	char *e;
	int l;

	l = mystrlen(name) + mystrlen(ac[0]) + 13;
	e = malloc(sizeof(char) * (l + 1));
	if (!e)
		return (NULL);

	mystrcpy(e, "alias: ");
	mystrcat(e, ac[0]);
	mystrcat(e, " not found\n");

	return (e);
}

/**
 * _exit_error - Creates an error message for myexit errors.
 * @ac: An array of arguments passed to the command.
 * Return: The error string.
 */
char *_exit_error(char **ac)
{
	char *e, *history_str;
	int l;

	history_str = myitoa(history_counter);
	if (!history_str)
		return (NULL);

	l = mystrlen(name) + mystrlen(history_str) + mystrlen(ac[0]) + 27;
	e = malloc(sizeof(char) * (l + 1));
	if (!e)
	{
		free(history_str);
		return (NULL);
	}

	mystrcpy(e, name);
	mystrcat(e, ": ");
	mystrcat(e, history_str);
	mystrcat(e, ": exit: Invalid number: ");
	mystrcat(e, ac[0]);
	mystrcat(e, "\n");

	free(history_str);
	return (e);
}

/**
 * directory_error - Creates an error message for mycd errors.
 * @ac: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *directory_error(char **ac)
{
	char *e, *history_str;
	int l;

	history_str = myitoa(history_counter);
	if (!history_str)
		return (NULL);

	if (ac[0][0] == '-')
		ac[0][2] = '\0';
	l = mystrlen(name) + mystrlen(history_str) + mystrlen(ac[0]) + 24;
	e = malloc(sizeof(char) * (l + 1));
	if (!e)
	{
		free(history_str);
		return (NULL);
	}

	mystrcpy(e, name);
	mystrcat(e, ": ");
	mystrcat(e, history_str);
	if (ac[0][0] == '-')
		mystrcat(e, ": cd: Invalid option ");
	else
		mystrcat(e, ": cd: can't cd to ");
	mystrcat(e, ac[0]);
	mystrcat(e, "\n");

	free(history_str);
	return (e);
}

/**
 * mysyntax - Creates an error message for syntax errors.
 * @ac: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *mysyntax(char **ac)
{
	char *e, *history_str;
	int l;

	history_str = myitoa(history_counter);
	if (!history_str)
		return (NULL);

	l = mystrlen(name) + mystrlen(history_str) + mystrlen(ac[0]) + 33;
	e = malloc(sizeof(char) * (l + 1));
	if (!e)
	{
		free(history_str);
		return (NULL);
	}

	mystrcpy(e, name);
	mystrcat(e, ": ");
	mystrcat(e, history_str);
	mystrcat(e, ": Syntax error: \"");
	mystrcat(e, ac[0]);
	mystrcat(e, "\" unexpected\n");

	free(history_str);
	return (e);
}
