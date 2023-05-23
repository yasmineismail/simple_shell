#include "shell.h"
/**
 * is_equal - checks if two strings are equal
 * @str1: string one
 * @str2: string two to compare with str1
 * Return: 1 if equal, 0 otherwise
 */
int is_equal(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}

	return (*str1 == '\0' && *str2 == '\0');
}

/**
 * write_string - writes a string to the standard output
 * @str: string to write
 * Return: void
 */
void write_string(const char *str)
{
	ssize_t len = 0;

	while (str[len] != '\0')
		len++;

	write(STDOUT_FILENO, str, len);
}
