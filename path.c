#include "shell.h"

char *_copy_path(char *path);
order_t *get_path_dir(char *path);

/**
 * _locate - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *_locate(char *command)
{
	char **path, *tmp;
	order_t *dirs, *head;
	struct stat st;

	path = get_env("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = mypath(*path + 5);
	head = dirs;

	while (dirs)
	{
		tmp = malloc(mystrlen(dirs->dir) + mystrlen(command) + 2);
		if (!tmp)
			return (NULL);

		mystrcpy(tmp, dirs->dir);
		mystrcat(tmp, "/");
		mystrcat(tmp, command);

		if (stat(tmp, &st) == 0)
		{
			myflist(head);
			return (tmp);
		}

		dirs = dirs->next;
		free(tmp);
	}

	myflist(head);

	return (NULL);
}

/**
 * _copy_path - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *_copy_path(char *path)
{
	int i, l = 0;
	char *path_copy, *pwd;

	pwd = *(get_env("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				l += mystrlen(pwd) + 1;
			else
				l++;
		}
		else
			l++;
	}
	path_copy = malloc(sizeof(char) * (l + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				mystrcat(path_copy, pwd);
				mystrcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				mystrcat(path_copy, ":");
				mystrcat(path_copy, pwd);
			}
			else
				mystrcat(path_copy, ":");
		}
		else
		{
			mystrncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * mypath - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
order_t *mypath(char *path)
{
	int index;
	char **dirs, *path_copy;
	order_t *head = NULL;

	path_copy = _copy_path(path);
	if (!path_copy)
		return (NULL);
	dirs = mystrtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_list_end(&head, dirs[index]) == NULL)
		{
			myflist(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}

