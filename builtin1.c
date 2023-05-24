#include "shell.h"


/**
 * _myhistory – Shows history list, one command by line, preceded
 *              with line numbers, starting from 0.
 * @info: The structure containing potential args. Used to maintain
 *        constant function prototype.
 *  Return: Always 0(success)
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}


/**
 * unset_alias – will set alias to string
 * @info: Parameter structure
 * @str: String alias
 *
 * Return: Always 0 (success), 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *s, d;
	int ret;


	s = _strchr(str, '=');
	if (!s)
		return (1);
	d = *s;
	*s = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*s = d;
	return (ret);
}


/**
 * set_alias – Will set alias to string
 * @info: Parameter structure
 * @str: String alias
 *
 * Return: Always 0(success), 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *s;


	s = _strchr(str, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (unset_alias(info, str));


	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}


/**
 * print_alias – Will print alias string
 * @node: Alias node
 *
 * Return: Always 0(success), 1 on error
 */
int print_alias(list_t *node)
{
	char *s = NULL, *a = NULL;


	if (node)
	{
		s = _strchr(node->str, '=');
		for (a = node->str; a <= s; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(s + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


/**
 * _myalias – Will mimic alias builtin
 * @info: The structure containing potential args. Used to maintain
 *          constant function prototype.
 *  Return: Always 0(success)
 */
int _myalias(info_t *info)
{
	int ui = 0;
	char *s = NULL;
	list_t *node = NULL;


	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (ui = 1; info->argv[ui]; ui++)
	{
		s = _strchr(info->argv[ui], '=');
		if (s)
			set_alias(info, info->argv[ui]);
		else
			print_alias(node_starts_with(info->alias, info->argv[ui], '='));
	}


	return (0);
}

