#include "shell.h"

char *mystrchr(char *s, char ch);
int mystrspn(char *s, char *accept);
int mystrcmp(char *s1, char *s2);
int mystrncmp(const char *s1, const char *s2, size_t n);

/**
 * mystrchr - Locates a character in a string.
 * @s: The string to be searched.
 * @ch: The character to be located.
 *
 * Return: If c is found - a pointer to the first occurence.
 *         If c is not found - NULL.
 */
char *mystrchr(char *s, char ch)
{
	int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] == ch)
			return (s + i);
	}

	return (NULL);
}

/**
 * mystrspn - Gets the length of a prefix substring.
 * @s: The string to be searched.
 * @accept: The prefix to be measured.
 *
 * Return: The number of bytes in s which
 *         consist only of bytes from accept.
 */
int mystrspn(char *s, char *accept)
{
	int b = 0;
	int i;

	while (*s)
	{
		for (i = 0; accept[i]; i++)
		{
			if (*s == accept[i])
			{
				b++;
				break;
			}
		}
		s++;
	}
	return (b);
}

/**
 * mystrcmp - Compares two strings.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 *
 * Return: Positive byte difference if s1 > s2
 *         0 if s1 = s2
 *         Negative byte difference if s1 < s2
 */
int mystrcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * mystrncmp - Compare two strings.
 * @s1: Pointer to a string.
 * @s2: Pointer to a string.
 * @n: The first n bytes of the strings to compare.
 *
 * Return: Less than 0 if s1 is shorter than s2.
 *         0 if s1 and s2 match.
 *         Greater than 0 if s1 is longer than s2.
 */
int mystrncmp(const char *s1, const char *s2, size_t n)
{
	size_t k;

	for (k = 0; s1[k] && s2[k] && k < n; k++)
	{
		if (s1[k] > s2[k])
			return (s1[k] - s2[k]);
		else if (s1[k] < s2[k])
			return (s1[k] - s2[k]);
	}
	if (k == n)
		return (0);
	else
		return (-15);
}

