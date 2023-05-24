#include "shell.h"


/**
 * _erratoi – Will convert string to int
 * @p: String to be converted
 * Return: 0 if no numbers in string, converted number otherwise,
 *       -1 on error
 */
int _erratoi(char *p)
{
	int ui = 0;
	unsigned long int result = 0;


	if (*p == '+')
		p++;  /* TODO: why does this make main return 255? */
	for (ui = 0;  p[ui] != '\0'; ui++)
	{
		if (p[ui] >= '0' && p[ui] <= '9')
		{
			result *= 10;
			result += (p[ui] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}


/**
 * print_error – Will print error message
 * @info: Parameter & return info structure
 * @estr: String containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise,
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}


/**
 * print_d – The function prints a decimal(int) number(base 10)
 * @input: Input
 * @fd: Filedescriptor to be written to
 *
 * Return: Number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int ui, count = 0;
	unsigned int _abs_, current;


	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (ui = 1000000000; ui > 1; ui /= 10)
	{
		if (_abs_ / ui)
		{
			__putchar('0' + current / ui);
			count++;
		}
		current %= ui;
	}
	__putchar('0' + current);
	count++;

	return (count);
}


/**
 * convert_number – The converter function
 * @num: Number
 * @base: Base
 * @flags: Arg flags
 *
 * Return: String
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;


	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';


	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';


	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);


	if (sign)
		*--ptr = sign;
	return (ptr);
}


/**
 * remove_comments – The function will replace first instance of ‘#’
 * with ‘\0’
 * @buf: Address of the string to modify
 *
 * Return: Always 0(success);
 */
void remove_comments(char *buf)
{
	int ui;


	for (ui = 0; buf[ui] != '\0'; ui++)
		if (buf[ui] == '#' && (!ui || buf[ui - 1] == ' '))
		{
			buf[ui] = '\0';
			break;
		}
}

