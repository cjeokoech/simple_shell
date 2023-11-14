#include "shell.h"

int mystrlen(const char *s);
char *mystrcpy(char *dest, const char *src);
char *mystrcat(char *dest, const char *src);
char *mystrncat(char *dest, const char *src, size_t n);

/**
 * mystrlen - Returns the length of a string.
 * @s: A pointer to the characters string.
 *
 * Return: The length of the character string.
 */
int mystrlen(const char *s)
{
	int l = 0;

	if (!s)
		return (l);
	for (l = 0; s[l]; l++)
		;
	return (l);
}

/**
 * mystrcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: Pointer to dest.
 */
char *mystrcpy(char *dest, const char *src)
{
	size_t k;

	for (k = 0; src[k] != '\0'; k++)
		dest[k] = src[k];
	dest[k] = '\0';
	return (dest);
}

/**
 * mystrcat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *mystrcat(char *dest, const char *src)
{
	char *dest_str;
	const char *src_str;

	dest_str = dest;
	src_str =  src;

	while (*dest_str != '\0')
		dest_str++;

	while (*src_str != '\0')
		*dest_str++ = *src_str++;
	*dest_str = '\0';
	return (dest);
}

/**
 * mystrncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *mystrncat(char *dest, const char *src, size_t n)
{
	size_t l = mystrlen(dest);
	size_t k;

	for (k = 0; k < n && src[k] != '\0'; k++)
		dest[l + k] = src[k];
	dest[l + k] = '\0';

	return (dest);
}

