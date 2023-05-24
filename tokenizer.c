#include "shell.h"


/**
 * **strtow – Will split str into words. Repeated delimiters are ignored
 * @str: Input str
 * @d: Delimeter str
 * Return: Pointer to array of strings, or NULL on failure
 */


char **strtow(char *str, char *d)
{
	int ui, j, k, m, numwords = 0;
	char **s;


	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (ui = 0; str[ui] != '\0'; ui++)
		if (!is_delim(str[ui], d) && (is_delim(str[ui + 1], d) || !str[ui + 1]))
			numwords++;


	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (ui = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[ui], d))
			ui++;
		k = 0;
		while (!is_delim(str[ui + k], d) && str[ui + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[ui++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}


/**
 * **strtow2 – Will split str into words
 * @str: Input str
 * @d: Delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int ui, j, k, m, numwords = 0;
	char **s;


	if (str == NULL || str[0] == 0)
		return (NULL);
	for (ui = 0; str[ui] != '\0'; ui++)
		if ((str[ui] != d && str[ui + 1] == d) ||
		    (str[ui] != d && !str[ui + 1]) || str[ui + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (ui = 0, j = 0; j < numwords; j++)
	{
		while (str[ui] == d && str[ui] != d)
			ui++;
		k = 0;
		while (str[ui + k] != d && str[ui + k] && str[ui + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[ui++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

