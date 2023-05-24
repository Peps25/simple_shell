#include "shell.h"


/**
 **_memset – Will fill the memory with a const byte
 *@c: Pointer to the memory area
 *@b: Byte to be used to fill *s
 *@n: Amount of bytes to be filled
 *Return: (c), a pointer to the memory area c
 */
char *_memset(char *c, char b, unsigned int n)
{
	unsigned int ui;


	for (ui = 0; ui < n; ui++)
		c[ui] = b;
	return (c);
}


/**
 * ffree – Will free a string of strings
 * @pp: Str of strings
 */
void ffree(char **pp)
{
	char **a = pp;


	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}


/**
 * _realloc – Will reallocate a block of memory
 * @ptr: Pointer to the previous mallocated block
 * @old_size: The byte size of old/previous block
 * @new_size: The byte size of the new block
 *
 * Return: Pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;


	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);


	p = malloc(new_size);
	if (!p)
		return (NULL);


	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

