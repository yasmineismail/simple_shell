#include "shell.h"
/**
 * is_builtin - checks if the given command is a built-in command
 * @args: arguments
 * Return: builtin
 */
int is_builtin(char **args)
{
	int builtin = 0;

	if (is_equal(args[0], "exit"))
		builtin = shell_exit(args);
	else if (is_equal(args[0], "env"))
		builtin = shell_env(args);
	else if (is_equal(args[0], "setenv"))
		builtin = shell_setenv(args);
	else if (is_equal(args[0], "unsetenv"))
		builtin = shell_unsetenv(args);
	else if (is_equal(args[0], "cd"))
		builtin = shell_cd(args);

	return (builtin);
}
