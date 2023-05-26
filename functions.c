#include "shell.h"

/**
 * is_interactive - checks if the shell is in interactive mode
 * @info: struct address
 * Return: 1 or 0
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfiled <= 2);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: the character to be checked
 * @del: the delimeter string
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_delimiter(char c, char *del)
{
	while (*del)
		if (*del++ == c)
			return (1);
	return (0);
}

/**
 *is_alpha - checks if character is alpha
 *@c: the input
 *Return: 1 if ture, 0 otherwise
 */

int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *string_integer - changes a string into an integer
 *@s: the string to be changed
 *Return: 0 if there are no numbers in the string, converted number otherwise
 */

int string_integer(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
