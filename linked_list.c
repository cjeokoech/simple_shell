#include "shell.h"

char_t *add_node_list(char_t **head, char *name, char *value);
void free_alias(char_t *head);
order_t *add_list_end(order_t **head, char *dir);
void myflist(order_t *head);

/**
 * add_node_list - Adds a node to the end of a alias_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
char_t *add_node_list(char_t **head, char *name, char *value)
{
	char_t *new = malloc(sizeof(char_t));
	char_t *last;

	if (!new)
		return (NULL);

	new->next = NULL;
	new->name = malloc(sizeof(char) * (mystrlen(name) + 1));
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	new->value = value;
	mystrcpy(new->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
	else
		*head = new;

	return (new);
}

/**
 * add_list_end - Adds a node to the end of a list_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
order_t *add_list_end(order_t **head, char *dir)
{
	order_t *new = malloc(sizeof(order_t));
	order_t *last;

	if (!new)
		return (NULL);

	new->dir = dir;
	new->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
	else
		*head = new;

	return (new);
}

/**
 * free_alias - Frees a char_t linked list.
 * @head: THe head of the char_t list.
 */
void free_alias(char_t *head)
{
	char_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

/**
 * myflist - Frees a list_t linked list.
 * @head: The head of the list_t list.
 */
void myflist(order_t *head)
{
	order_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}

