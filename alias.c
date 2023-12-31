#include "shell.h"

int _alias(char **ac, char __attribute__((__unused__)) **ptr);
void _setalias(char *alias_name, char *value);
void myprintalias(char_t *alias);

/**
 * _alias - Builtin command that either prints all aliases
 * @ac: An array of arguments.
 * @ptr: A double pointer to the beginning of a.
 *
 * Return: 0
 */
int _alias(char **ac, char __attribute__((__unused__)) **ptr)
{
	char_t *tmp = aliases;
	int i, r = 0;
	char *value;

	if (!ac[0])
	{
		while (tmp)
		{
			myprintalias(tmp);
			tmp = tmp->next;
		}
		return (r);
	}
	for (i = 0; ac[i]; i++)
	{
		tmp = aliases;
		value = mystrchr(ac[i], '=');
		if (!value)
		{
			while (tmp)
			{
				if (mystrcmp(ac[i], tmp->name) == 0)
				{
					myprintalias(tmp);
					break;
				}
				tmp = tmp->next;
			}
			if (!tmp)
				r = myerror(ac + i, 1);
		}
		else
			_setalias(ac[i], value);
	}
	return (r);
}

/**
 * _setalias - Will either set an existing alias
 * @alias_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void _setalias(char *alias_name, char *value)
{
	char_t *tmp = aliases;
	int l, j, k;
	char *new;

	*value = '\0';
	value++;
	l = mystrlen(value) - mystrspn(value, "'\"");
	new = malloc(sizeof(char) * (l + 1));
	if (!new)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new[k++] = value[j];
	}
	new[k] = '\0';
	while (tmp)
	{
		if (mystrcmp(alias_name, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = new;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_node_list(&aliases, alias_name, new);
}

/**
 * myprintalias - Prints the alias in the format name='value'.
 * @p: Pointer to an alias.
 */
void myprintalias(char_t *p)
{
	char *str;
	int l = mystrlen(p->name) + mystrlen(p->value) + 4;

	str = malloc(sizeof(char) * (l + 1));
	if (!str)
		return;
	mystrcpy(str, p->name);
	mystrcat(str, "='");
	mystrcat(str, p->value);
	mystrcat(str, "'\n");

	write(STDOUT_FILENO, str, l);
	free(str);
}
/**
 * myalias - Goes through the arguments and replace any matching alias
 * @ac: pointer to the arguments.
 *
 * Return: pointer to the arguments.
 */
char **myalias(char **ac)
{
	char_t *tmp;
	int i;
	char *new;

	if (mystrcmp(ac[0], "alias") == 0)
		return (ac);
	for (i = 0; ac[i]; i++)
	{
		tmp = aliases;
		while (tmp)
		{
			if (mystrcmp(ac[i], tmp->name) == 0)
			{
				new = malloc(sizeof(char) * (mystrlen(tmp->value) + 1));
				if (!new)
				{
					free_memory(ac, ac);
					return (NULL);
				}
				mystrcpy(new, tmp->value);
				free(ac[i]);
				ac[i] = new;
				i--;
				break;
			}
			tmp = tmp->next;
		}
	}

	return (ac);
}

