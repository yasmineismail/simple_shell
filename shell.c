#include "shell.h"
/**
 * shell_exit - exit the shell
 * @args: arguments
 * Return: int
 */
int shell_exit(char **args)
{
	if (args[1] != NULL)
	{
		int status = atoi(args[1]);

		exit(status);
	}
	exit(EXIT_SUCCESS);
}

/**
 * shell_env - prints out the environment variables in the shell
 * @args: arguments
 * Return: 1
 */
int shell_env(char **args __attribute__((unused)))
{
	extern char **environ;
	char **env = environ;

	while (*env != NULL)
	{
		write_string(*env);
		write_string("\n");
		env++;
	}

	return (1);
}

/**
 * shell_setenv - modifies an environment variable in the shell
 * @args: arguments
 * Return: 1
 */
int shell_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		write_string("Usage: setenv <variable> <value>\n");
		return (1);
	}

	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
	}

	return (1);
}

/**
 * shell_unsetenv - removes an environment variable from the shell
 * @args: arguments
 * Return: 1
 */
int shell_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		write_string("Usage: unsetenv <variable>\n");
		return (1);
	}

	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
	}

	return (1);
}

/**
 * shell_cd - allows the user to change the current working directory
 * @args: arguments
 * Return: 1
 */
int shell_cd(char **args)
{
	if (args[1] == NULL)
	{
		write_string("Usage: cd <directory>\n");
		return (1);
	}

	if (chdir(args[1]) != 0)
	{
		perror("cd");
	}

	return (1);
}
