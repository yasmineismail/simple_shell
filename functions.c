#include "shell.h"
/**
 * read_line - reads a line from standard input
 * Return: the line read
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	getline(&line, &bufsize, stdin);
	return (line);
}
/**
 * split_line - splits line
 * @line: char
 * Return: tokens
 */
char **split_line(char *line)
{
	int bufsize = BUFFER_SIZE;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\n\r\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += BUFFER_SIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("Allocation error");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\n\r\a");
	}
	tokens[position] = NULL;

	return (tokens);
}

/**
 * execute_command - execute command
 * @args: arguments
 * Return: 1
 */
int execute_command(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return (1);

	if (is_builtin(args))
		return (1);

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			write_string("Command not found\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		write_string("Fork failed\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}
