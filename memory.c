#include "shell.h"

void free_memory(char **ac, char **ptr);
char *mypid(void);
char *_env_value(char *begin, int l);
void myvariable(char **ac, int *exect);

/**
 * free_memory - Frees up memory taken by args.
 * @ac: A null-terminated double pointer containing commands/arguments.
 * @ptr: A double pointer to the beginning of ac.
 */
void free_memory(char **ac, char **ptr)
{
	size_t k;

	for (k = 0; ac[k] || ac[k + 1]; k++)
		free(ac[k]);

	free(ptr);
}

/**
 * mypid - Gets the current process ID.
 * Return: The current process ID or NULL on failure.
 */
char *mypid(void)
{
	size_t k = 0;
	char *b;
	ssize_t f;

	f = open("/proc/self/stat", O_RDONLY);
	if (f == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	b = malloc(120);
	if (!b)
	{
		close(f);
		return (NULL);
	}
	read(f, b, 120);
	while (b[k] != ' ')
		k++;
	b[k] = '\0';

	close(f);
	return (b);
}

/**
 * _env_value - Gets the value corresponding to an environmental variable.
 * @begin: The environmental variable to search for.
 * @l: The length of the environmental variable to search for.
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 */
char *_env_value(char *begin, int l)
{
	char **variable_address;
	char *replace = NULL, *tmp, *var;

	var = malloc(l + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	mystrncat(var, begin, l);

	variable_address = get_env(var);
	free(var);
	if (variable_address)
	{
		tmp = *variable_address;
		while (*tmp != '=')
			tmp++;
		tmp++;
		replace = malloc(mystrlen(tmp) + 1);
		if (replace)
			mystrcpy(replace, tmp);
	}

	return (replace);
}

/**
 * myvariable - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exect: A pointer to the return value of the last executed command.
 */
void myvariable(char **line, int *exect)
{
	int j, k = 0, l;
	char *replace = NULL, *old = NULL, *new;

	old = *line;
	for (j = 0; old[j]; j++)
	{
		if (old[j] == '$' && old[j + 1] &&
				old[j + 1] != ' ')
		{
			if (old[j + 1] == '$')
			{
				replace = mypid();
				k = j + 2;
			}
			else if (old[j + 1] == '?')
			{
				replace = myitoa(*exect);
				k = j + 2;
			}
			else if (old[j + 1])
			{
				for (k = j + 1; old[k] &&
						old[k] != '$' &&
						old[k] != ' '; k++)
					;
				l = k - (j + 1);
				replace = _env_value(&old[j + 1], l);
			}
			new = malloc(j + mystrlen(replace)
					  + mystrlen(&old[k]) + 1);
			if (!line)
				return;
			new[0] = '\0';
			mystrncat(new, old, j);
			if (replace)
			{
				mystrcat(new, replace);
				free(replace);
				replace = NULL;
			}
			mystrcat(new, &old[k]);
			free(old);
			*line = new;
			old = new;
			j = -1;
		}
	}
}

