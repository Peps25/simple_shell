#include "shell.h"

/**
 * interactive – Will return “true” if shell is on interactive mode
 * @info: Structure address
 *
 * Return: 1 if on interactive mode, 0 if not
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}


/**
 * is_delim – will check if the char is a delimeter
 * @d: Character that will be checked
 * @delim: Delimeter string
 * Return: 1 if it is true, 0 if false
 */

int is_delim(char d, char *delim)
{
	while (*delim)
		if (*delim++ == d)
			return (1);
	return (0);
}

/**
 * _isalpha – Will check for alphabetic char
 * @d: character to be inputted
 * Return: 1 if d is an alphabet, 0 if not
 */


int _isalpha(int d)
{
	if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Will convert str to int
 * @p: string that will be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */


int _atoi(char *s)
{
	int ui, sign = 1, flag = 0, output;
	unsigned int result = 0;


	for (ui = 0;  s[ui] != '\0' && flag != 2; ui++)
	{
		if (s[ui] == '-')
			sign *= -1;


		if (s[ui] >= '0' && s[ui] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[ui] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}


	if (sign == -1)
		output = -result;
	else
		output = result;


	return (output);
}

