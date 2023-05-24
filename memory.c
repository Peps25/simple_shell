#include "shell.h"


/**
 * bfree – Will free a pointer and NULL the address
 * @ptr: The address of the pointer to be freed
 *
 * Return: 1 if pointer is freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

