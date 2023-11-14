#include "shell.h"

char *get_command(char *line, int *exect);
int call_command(char **ac, char **ptr, int *exect);
int execute_command(char **ac, char **ptr, int *exect);
int handle_command(int *exect);
int check_command(char **ac);

/**
 * get_command - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exect: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_command(char *line, int *exect)
{
	size_t n = 0;
	ssize_t r;
	char *prompt = "$ ";

	if (line)
		free(line);

	r = mygetline(&line, &n, STDIN_FILENO);
	if (r == -1)
		return (NULL);
	if (r == 1)
	{
		history_counter++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_command(line, exect));
	}

	line[r - 1] = '\0';
	myvariable(&line, exect);
	_get_line(&line, r);

	return (line);
}

/**
 * call_command - Partitions operators from commands and calls them.
 * @ac: An array of arguments.
 * @ptr: A double pointer to the beginning of ac.
 * @exect: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int call_command(char **ac, char **ptr, int *exect)
{
	int r, index;

	if (!ac[0])
		return (*exect);
	for (index = 0; ac[index]; index++)
	{
		if (mystrncmp(ac[index], "||", 2) == 0)
		{
			free(ac[index]);
			ac[index] = NULL;
			ac = myalias(ac);
			r = execute_command(ac, ptr, exect);
			if (*exect != 0)
			{
				ac = &ac[++index];
				index = 0;
			}
			else
			{
				for (index++; ac[index]; index++)
					free(ac[index]);
				return (r);
			}
		}
		else if (mystrncmp(ac[index], "&&", 2) == 0)
		{
			free(ac[index]);
			ac[index] = NULL;
			ac = myalias(ac);
			r = execute_command(ac, ptr, exect);
			if (*exect == 0)
			{
				ac = &ac[++index];
				index = 0;
			}
			else
			{
				for (index++; ac[index]; index++)
					free(ac[index]);
				return (r);
			}
		}
	}
	ac = myalias(ac);
	r = execute_command(ac, ptr, exect);
	return (r);
}

/**
 * execute_command - Calls the execution of a command.
 * @ac: An array of arguments.
 * @ptr: A double pointer to the beginning of args.
 * @exect: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int execute_command(char **ac, char **ptr, int *exect)
{
	int r, i;
	int (*builtin)(char **ac, char **ptr);

	builtin = _builtin(ac[0]);

	if (builtin)
	{
		r = builtin(ac + 1, ptr);
		if (r != EXIT)
			*exect = r;
	}
	else
	{
		*exect = myexecve(ac, ptr);
		r = *exect;
	}

	history_counter++;

	for (i = 0; ac[i]; i++)
		free(ac[i]);

	return (r);
}

/**
 * handle_command - Gets, calls, and runs the execution of a command.
 * @exect: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_command(int *exect)
{
	int r = 0, index;
	char **ac, *line = NULL, **ptr;

	line = get_command(line, exect);
	if (!line)
		return (END_OF_FILE);

	ac = mystrtok(line, " ");
	free(line);
	if (!ac)
		return (r);
	if (check_command(ac) != 0)
	{
		*exect = 2;
		free_memory(ac, ac);
		return (*exect);
	}
	ptr = ac;

	for (index = 0; ac[index]; index++)
	{
		if (mystrncmp(ac[index], ";", 1) == 0)
		{
			free(ac[index]);
			ac[index] = NULL;
			r = call_command(ac, ptr, exect);
			ac = &ac[++index];
			index = 0;
		}
	}
	if (ac)
		r = call_command(ac, ptr, exect);

	free(ptr);
	return (r);
}

/**
 * check_command - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @ac: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_command(char **ac)
{
	size_t i;
	char *c, *n;

	for (i = 0; ac[i]; i++)
	{
		c = ac[i];
		if (c[0] == ';' || c[0] == '&' || c[0] == '|')
		{
			if (i == 0 || c[1] == ';')
				return (myerror(&ac[i], 2));
			n = ac[i + 1];
			if (n && (n[0] == ';' || n[0] == '&' || n[0] == '|'))
				return (myerror(&ac[i + 1], 2));
		}
	}
	return (0);
}

