#include "shell.h"


/**
 *_eputs – Will print input string
 * @str: String to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int ui = 0;


	if (!str)
		return;
	while (str[ui] != '\0')
	{
		_eputchar(str[ui]);
		ui++;
	}
}


/**
 * _eputchar – Will write character d to stderr
 * @d: Character to be printed
 *
 * Return: On success 1.
 * -1 on error, and errno is set appropriately.
 */
int _eputchar(char d)
{
	static int ui;
	static char buf[WRITE_BUF_SIZE];


	if (d == BUF_FLUSH || ui >= WRITE_BUF_SIZE)
	{
		write(2, buf, ui);
		ui = 0;
	}
	if (d != BUF_FLUSH)
		buf[ui++] = d;
	return (1);
}


/**
 * _putfd – Will write character d to given fd
 * @d: Character to print/write
 * @fd: filedescriptor to be written to
 *
 * Return: On success 1.
 * -1 on error, and errno is set appropriately.
 */
int _putfd(char d, int fd)
{
	static int ui;
	static char buf[WRITE_BUF_SIZE];


	if (d == BUF_FLUSH || ui >= WRITE_BUF_SIZE)
	{
		write(fd, buf, ui);
		ui = 0;
	}
	if (d != BUF_FLUSH)
		buf[ui++] = d;
	return (1);
}


/**
 *_putsfd – Will print input string
 * @str: String to print
 * @fd: filedescriptor to be written to
 *
 * Return: the number of characters put
 */
int _putsfd(char *str, int fd)
{
	int ui = 0;


	if (!str)
		return (0);
	while (*str)
	{
		ui += _putfd(*str++, fd);
	}
	return (ui);
}

