#include "shell.h"

char **copy_env(void);
void _free_env(void);
char **get_env(const char *env_var);

/**
 * copy_env - Creates a copy of the environment.
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **copy_env(void)
{
	char **new_env;
	size_t size;
	int i;

	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		new_env[i] = malloc(mystrlen(environ[i]) + 1);

		if (!new_env[i])
		{
			for (i--; i >= 0; i--)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		mystrcpy(new_env[i], environ[i]);
	}
	new_env[i] = NULL;

	return (new_env);
}

/**
 * _free_env - Frees the the environment copy.
 */
void _free_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
 * get_env - Gets an environmental variable from the PATH.
 * @env_var: The name of the environmental variable to get.
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **get_env(const char *env_var)
{
	int i, l;

	l = mystrlen(env_var);
	for (i = 0; environ[i]; i++)
	{
		if (mystrncmp(env_var, environ[i], l) == 0)
			return (&environ[i]);
	}

	return (NULL);
}

