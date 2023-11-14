#include "shell.h"

int myenv(char **ac, char __attribute__((__unused__)) **ptr);
int _setenv(char **ac, char __attribute__((__unused__)) **ptr);
int _unsetenv(char **ac, char __attribute__((__unused__)) **ptr);

/**
 * myenv - Prints the current environment.
 * @ac: An array of arguments passed to the shell.
 * @ptr: A double pointer to the beginning of ac.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 */
int myenv(char **ac, char __attribute__((__unused__)) **ptr)
{
	int ix;
	char n = '\n';

	if (!environ)
		return (-1);

	for (ix = 0; environ[ix]; ix++)
	{
		write(STDOUT_FILENO, environ[ix], mystrlen(environ[ix]));
		write(STDOUT_FILENO, &n, 1);
	}

	(void)ac;
	return (0);
}

/**
 * _setenv - Changes or adds an environmental variable to the PATH.
 * @ac: An array of arguments passed to the shell.
 * @ptr: A double pointer to the beginning of args.
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int _setenv(char **ac, char __attribute__((__unused__)) **ptr)
{
	char **env_variable = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!ac[0] || !ac[1])
		return (myerror(ac, -1));

	new_value = malloc(mystrlen(ac[0]) + 1 + mystrlen(ac[1]) + 1);
	if (!new_value)
		return (myerror(ac, -1));
	mystrcpy(new_value, ac[0]);
	mystrcat(new_value, "=");
	mystrcat(new_value, ac[1]);

	env_variable = get_env(ac[0]);
	if (env_variable)
	{
		free(*env_variable);
		*env_variable = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (myerror(ac, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * _unsetenv - Deletes an environmental variable from the PATH.
 * @ac: An array of arguments passed to the shell.
 * @ptr: A double pointer to the beginning of ac.
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int _unsetenv(char **ac, char __attribute__((__unused__)) **ptr)
{
	char **env_variable, **new_environ;
	size_t size;
	int index, index2;

	if (!ac[0])
		return (myerror(ac, -1));
	env_variable = get_env(ac[0]);
	if (!env_variable)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (myerror(ac, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_variable == environ[index])
		{
			free(*env_variable);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}

