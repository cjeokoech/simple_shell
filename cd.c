#include "shell.h"
int (*_builtin(char *command))(char **ac, char **ptr);
int myexit(char **ac, char **ptr);
int mycd(char **ac, char __attribute__((__unused__)) **ptr);
int _help(char **ac, char __attribute__((__unused__)) **ptr);

/**
 * _builtin - Matches a command with a corresponding
 * @command: The command to match.
 * Return: A function pointer to the corresponding builtin.
 */
int (*_builtin(char *command))(char **ac, char **ptr)
{
	builtin_t funcs[] = {
		{ "exit", myexit },
		{ "env", myenv },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", mycd },
		{ "alias", _alias },
		{ "help", _help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (mystrcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * myexit - Causes normal process termination of hell
 * @ac: An array of arguments containing the exit value.
 * @ptr: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 */
int myexit(char **ac, char **ptr)
{
	int i, l = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (ac[0])
	{
		if (ac[0][0] == '+')
		{
			i = 1;
			l++;
		}
		for (; ac[0][i]; i++)
		{
			if (i <= l && ac[0][i] >= '0' && ac[0][i] <= '9')
				num = (num * 10) + (ac[0][i] - '0');
			else
				return (myerror(--ac, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (myerror(--ac, 2));
	ac -= 1;
	free_memory(ac, ptr);
	_free_env();
	free_alias(aliases);
	exit(num);
}

/**
 * mycd - Changes the current directory of the shell process.
 * @ac: An array of arguments.
 * @ptr: A double pointer to the beginning of args.
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int mycd(char **ac, char __attribute__((__unused__)) **ptr)
{
	char **info, *new = "\n";
	char *old_pwd = NULL, *pwd = NULL;
	struct stat dir;

	old_pwd = getcwd(old_pwd, 0);
	if (!old_pwd)
		return (-1);

	if (ac[0])
	{
		if (*(ac[0]) == '-' || mystrcmp(ac[0], "--") == 0)
		{
			if ((ac[0][1] == '-' && ac[0][2] == '\0') ||
					ac[0][1] == '\0')
			{
				if (get_env("OLDPWD") != NULL)
					(chdir(*get_env("OLDPWD") + 7));
			}
			else
			{
				free(old_pwd);
				return (myerror(ac, 2));
			}
		}
		else
		{
			if (stat(ac[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(ac[0]);
			else
			{
				free(old_pwd);
				return (myerror(ac, 2));
			}
		}
	}
	else
	{
		if (get_env("HOME") != NULL)
			chdir(*(get_env("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	info = malloc(sizeof(char *) * 2);
	if (!info)
		return (-1);

	info[0] = "OLDPWD";
	info[1] = old_pwd;
	if (_setenv(info, info) == -1)
		return (-1);

	info[0] = "PWD";
	info[1] = pwd;
	if (_setenv(info, info) == -1)
		return (-1);
	if (ac[0] && ac[0][0] == '-' && ac[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, mystrlen(pwd));
		write(STDOUT_FILENO, new, 1);
	}
	free(old_pwd);
	free(pwd);
	free(info);
	return (0);
}

/**
 * _help - Displays information about shell builtin commands.
 * @ac: An array of arguments.
 * @ptr: A pointer to the beginning of args
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int _help(char **ac, char __attribute__((__unused__)) **ptr)
{
	if (!ac[0])
		print_builtin();
	else if (mystrcmp(ac[0], "alias") == 0)
		print_alias();
	else if (mystrcmp(ac[0], "cd") == 0)
		print_cd();
	else if (mystrcmp(ac[0], "exit") == 0)
		print_exit();
	else if (mystrcmp(ac[0], "env") == 0)
		print_env();
	else if (mystrcmp(ac[0], "setenv") == 0)
		print_setenv();
	else if (mystrcmp(ac[0], "unsetenv") == 0)
		print_unsetenv();
	else if (mystrcmp(ac[0], "help") == 0)
		print_help();
	else
		write(STDERR_FILENO, name, mystrlen(name));

	return (0);
}

