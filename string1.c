#include "shell.h"


/**
 * _strcpy – will copy a str
 * @dest: Destination
 * @src: Source
 *
 * Return: Pointer to the destination
 */
char *_strcpy(char *dest, char *src)
{
	int ui = 0;


	if (dest == src || src == 0)
		return (dest);
	while (src[ui])
	{
		dest[ui] = src[ui];
		ui++;
	}
	dest[ui] = 0;
	return (dest);
}


/**
 * _strdup – Will duplicate str
 * @str: Str to be duplicated
 *
 * Return: Pointer to duplicated str
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;


	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}


/**
 *_puts – Will print input str
 *@str: String to print
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int ui = 0;


	if (!str)
		return;
	while (str[ui] != '\0')
	{
		_putchar(str[ui]);
		ui++;
	}
}


/**
 * _putchar – Will write char c to stdout
 * @c: Char to be printed
 *
 * Return: On success 1.
 * -1 on error, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int ui;
	static char buf[WRITE_BUF_SIZE];


	if (c == BUF_FLUSH || ui >= WRITE_BUF_SIZE)
	{
		write(1, buf, ui);
		ui = 0;
	}
	if (c != BUF_FLUSH)
		buf[ui++] = c;
	return (1);
}

