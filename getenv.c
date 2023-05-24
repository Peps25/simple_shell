#include "shell.h"


/**
 * get_environ – Will return string array copy of our environment
 * @info: The structure containing potential args. Used to maintain
 *          constant function prototype.
 * Return: Always 0(success)
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}


	return (info->environ);
}


/**
 * _unsetenv – Will remove environ var
 * @info: The structure containing potential args. Used to maintain
 *        constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: String env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t ui = 0;
	char *s;


	if (!node || !var)
		return (0);


	while (node)
	{
		s = starts_with(node->str, var);
		if (s && *s == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			ui = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		ui++;
	}
	return (info->env_changed);
}


/**
 * _setenv – Will initialize a new environ var,
 *             or modify an existing one
 * @info: The structure containing potential args. Used to maintain
 *        constant function prototype.
 * @var: String environ variable property
 * @value: String environ variable value
 *  Return: Always 0(success)
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *s;


	if (!var || !value)
		return (0);


	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		s = starts_with(node->str, var);
		if (s && *s == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

