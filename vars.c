#include "shell.h"


/**
 * is_chain – Will test if current character in buffer is a chain delimeter
 * @info: Parameter structure
 * @buf: Character buffer
 * @p: The address of the current position in the buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;


	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}


/**
 * check_chain - Checks if we should continue chaining based on last status
 * @info: Parameter structure
 * @buf: Character buffer
 * @p: The address of the current position in the buffer
 * @ui: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t ui, size_t len)
{
	size_t j = *p;


	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[ui] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[ui] = 0;
			j = len;
		}
	}


	*p = j;
}


/**
 * replace_alias – Will replace an alias in tokenized str
 * @info: Parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int ui;
	list_t *node;
	char *p;


	for (ui = 0; ui < 10; ui++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}


/**
 * replace_vars – Will replace variables in the tokenized str
 * @info: Parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int ui = 0;
	list_t *node;


	for (ui = 0; info->argv[ui]; ui++)
	{
		if (info->argv[ui][0] != '$' || !info->argv[ui][1])
			continue;


		if (!_strcmp(info->argv[ui], "$?"))
		{
			replace_string(&(info->argv[ui]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[ui], "$$"))
		{
			replace_string(&(info->argv[ui]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[ui][1], '=');
		if (node)
		{
			replace_string(&(info->argv[ui]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[ui], _strdup(""));


	}
	return (0);
}


/**
 * replace_string – Will replace the str
 * @old: The address of the old str
 * @new: New str
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

