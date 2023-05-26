#include "shell.h"

/**
 * get_environ - Returns a string array copy of the environ variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->envir_changed)
	{
		info->environ = list_to_strings(info->env);
		info->envir_changed = 0;
	}

	return (info->environ);
}

/**
 * un_setenv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * @var: The string representing the environment variable.
  * Return: Returns 1 if the var is successfully deleted, 0 otherwise.
 */
int un_setenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->envir_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->envir_changed);
}

/**
 * set_env - Sets up a new environment variable,
 *             or updates an existing one.
 * @info: Structure containing potential arguments.
 * @var: The string representing the environment variable
 * @value: The string env var value.
 * Return: Always 0
 */
int set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->envir_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->envir_changed = 1;
	return (0);
}
