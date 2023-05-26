#include "shell.h"
/**
 * bfree - Function to free a pointer and set its address to NULL.
 * @ptr: Address of the pointer to be freed.
 * Return: 1 if the pointer is successfully freed, otherwise 0.
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
