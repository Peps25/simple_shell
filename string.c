#include "shell.h"


/**
 * _strlen – Will return length of a str
 * @s: String whose length will be checked
 *
 * Return: int length of str
 */
int _strlen(char *s)
{
	int ui = 0;


	if (!s)
		return (0);


	while (*s++)
		ui++;
	return (ui);
}


/**
 * _strcmp – Will perform lexicogarphic comparison of two strings.
 * @s1: First str
 * @s2: Second str
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}


/**
 * starts_with – Will check if needle starts with haystack
 * @haystack: Str to search for
 * @needle: Substring to be found
 *
 * Return: Address of the next character of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}


/**
 * _strcat – Will concatenate two strings
 * @dest: Destination buffer
 * @src: Source buffer
 *
 * Return: The Pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;


	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

