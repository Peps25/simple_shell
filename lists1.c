#include "shell.h"


/**
 * list_len – Will determine the length of a linked list
 * @b: pointer to first node
 *
 * Return: The size of the list
 */
size_t list_len(const list_t *b)
{
	size_t ui = 0;


	while (b)
	{
		b = b->next;
		ui++;
	}
	return (ui);
}

/**
 * list_to_strings – Will return array of str of the list->str
 * @head: Pointer to the first node
 *
 * Return: An array of str
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t ui = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !ui)
		return (NULL);
	strs = malloc(sizeof(char *) * (ui + 1));
	if (!strs)
		return (NULL);
	for (ui = 0; node; node = node->next, ui++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < ui; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}


		str = _strcpy(str, node->str);
		strs[ui] = str;
	}
	strs[ui] = NULL;
	return (strs);
}




/**
 * print_list – Will print all elements of list_t linked list
 * @b: Pointer to the first node
 *
 * Return: The size of the list
 */
size_t print_list(const list_t *b)
{
	size_t ui = 0;


	while (b)
	{
		_puts(convert_number(b->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? b->str : "(nil)");
		_puts("\n");
		b = b->next;
		ui++;
	}
	return (ui);
}


/**
 * node_starts_with – Will return node whose str starts with a prefix
 * @node: Pointer to the list head
 * @prefix: Str to be matched
 * @c: The next char after prefix to be matched
 *
 * Return: Match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *s = NULL;


	while (node)
	{
		s = starts_with(node->str, prefix);
		if (s && ((c == -1) || (*s == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t ui = 0;


	while (head)
	{
		if (head == node)
			return (ui);
		head = head->next;
		ui++;
	}
	return (-1);
}

