#include "shell.h"

/**
 * my_env - Prints the current environment.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_env - Obtains the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment name.
 * Return: Char.
 */
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * myset_env - Sets up a new environment variable,
 *             or updates an existing one.
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int myset_env(info_t *info)
{
	if (info->argc != 3)
	{
		e_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * myunset_env - Remove an environment variable.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int myunset_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		e_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		un_setenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populates environment linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
