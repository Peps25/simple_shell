#include "shell.h"


/**
 * _myenv – Will print current environment
 * @info: The structure containing potential args. Used to maintain
 *          constant function prototype.
 * Return: Always 0(success)
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}


/**
 * _getenv – Will get value of environ variable
 * @info: The structure containing potential args. Used to maintain
 * @name: environ variable name
 *
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *s;


	while (node)
	{
		s = starts_with(node->str, name);
		if (s && *s)
			return (s);
		node = node->next;
	}
	return (NULL);
}


/**
 * _mysetenv – Will initialize a new environ var,
 *             or modify existing one
 * @info: The structure containing potential args. Used to maintain
 *        constant function prototype.
 *  Return: Always 0(success)
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}


/**
 * _myunsetenv – Will remove environ var
 * @info: The structure containing potential args. Used to maintain
 *        constant function prototype.
 *  Return: Always 0(success)
 */
int _myunsetenv(info_t *info)
{
	int ui;


	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (ui = 1; ui <= info->argc; ui++)
		_unsetenv(info, info->argv[ui]);


	return (0);
}


/**
 * populate_env_list – Will populate env linked list
 * @info: The structure containing potential args. Used to maintain
 *          constant function prototype.
 * Return: Always 0(success)
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t ui;


	for (ui = 0; environ[ui]; ui++)
		add_node_end(&node, environ[ui], 0);
	info->env = node;
	return (0);
}

