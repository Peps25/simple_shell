#include "shell.h"


/**
 **_strncpy – Will copy string
 *@dest: Destination string to be copied to
 *@src: Source string
 *@n: Amount of chars to be copied
 *Return: Concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int ui, j;
	char *p = dest;


	ui = 0;
	while (src[ui] != '\0' && ui < n - 1)
	{
		dest[ui] = src[ui];
		ui++;
	}
	if (ui < n)
	{
		j = ui;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (p);
}


/**
 **_strncat – Will concatenate two strings
 *@dest: First string
 *@src: Second string
 *@n: Maximum amount of bytes to be used
 *Return: Concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int ui, j;
	char *p = dest;


	ui = 0;
	j = 0;
	while (dest[ui] != '\0')
		ui++;
	while (src[j] != '\0' && j < n)
	{
		dest[ui] = src[j];
		ui++;
		j++;
	}
	if (j < n)
		dest[ui] = '\0';
	return (p);
}


/**
 **_strchr – Will locate char in a string
 *@p: String to be parsed
 *@d: Character to look for
 *Return: (p) a pointer to the memory area p
 */
char *_strchr(char *p, char d)
{
	do {
		if (*p == d)
			return (p);
	} while (*p++ != '\0');


	return (NULL);
}

