#include "shell.h"
/**
 **_memset - Function to fill memory with a constant byte.
 *@s: Pointer to the memory area.
 *@b: The byte to fill *s with.
 *@n: The number of bytes to be filled.
 *Return: A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - Function to free a string of strings.
 * @pp: String of strings to be freed.
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
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previously allocated block of memory.
 * @old_size: Size in bytes of the previous block.
 * @new_size: Size in bytes of the new block.
 * Return: Pointer to the reallocated block of memory.
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
