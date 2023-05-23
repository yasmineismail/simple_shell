#include "shell.h"
/**
 * main - Main program
 * Return: always 0
 */
int main(void)
{
	char *line;
	char **args;
	int status;

	do {
		write_string("$ ");
		line = read_line();
		args = split_line(line);
		status = execute_command(args);

		free(line);
		free(args);
	} while (status);
	return (0);
}
