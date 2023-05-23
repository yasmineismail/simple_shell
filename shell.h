#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *read_line(void);
char **split_line(char *line);
int execute_command(char **args);
int is_builtin(char **args);
int shell_exit(char **args);
int shell_env(char **args __attribute__((unused)));
int shell_setenv(char **args);
int shell_unsetenv(char **args);
int shell_cd(char **args);
int is_equal(const char *str1, const char *str2);
void write_string(const char *str);
#endif 
