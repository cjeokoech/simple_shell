#include "shell.h"

void _get_line(char **line, ssize_t read);
ssize_t new_length(char *line);
void logical_operator(char *line, ssize_t *l);

/**
 * _get_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 */
void _get_line(char **line, ssize_t read)
{
	char *old, *new;
	char previous, current, next;
	size_t i, j;
	ssize_t len;

	len = new_length(*line);
	if (len == read - 1)
		return;
	new = malloc(len + 1);
	if (!line)
		return;
	j = 0;
	old = *line;
	for (i = 0; old[i]; i++)
	{
		current = old[i];
		next = old[i + 1];
		if (i != 0)
		{
			previous = old[i - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new[j++] = ' ';
					new[j++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new[j++] = ';';
					new[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					new[j++] = ' ';
				new[j++] = ';';
				if (next != ' ')
					new[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new[j++] = '&';
					new[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new[j++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					new[j++] = '|';
					new[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old[i - 1] != ' ')
				new[j++] = ' ';
			new[j++] = ';';
			if (next != ' ' && next != ';')
				new[j++] = ' ';
			continue;
		}
		new[j++] = old[i];
	}
	new[j] = '\0';

	free(*line);
	*line = new;
}

/**
 * new_length - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t new_length(char *line)
{
	size_t i;
	ssize_t len = 0;
	char current, next;

	for (i = 0; line[i]; i++)
	{
		current = line[i];
		next = line[i + 1];
		if (current == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					len++;
				if (next != ' ')
					len++;
			}
			else
				logical_operator(&line[i], &len);
		}
		else if (current == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				len++;
			if (next != ' ' && next != ';')
				len++;
		}
		len++;
	}
	return (len);
}
/**
 * logical_operator - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @l: Pointer to l in new_length function.
 */
void logical_operator(char *line, ssize_t *l)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*l)++;
		else if (previous == '&' && next != ' ')
			(*l)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*l)++;
		else if (previous == '|' && next != ' ')
			(*l)++;
	}
}

