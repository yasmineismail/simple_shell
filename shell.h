#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststring - Linked list.
 * @num: The number field.
 * @str: String.
 * @next: Points to the next node.
 */
typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: A string generated from getline that contains arguments.
 *@argv: An array of strings generated from arg.
 *@path: A string representing the current command's path.
 *@argc: The count of arguments.
 *@count_of_line: The count of errors.
 *@error_nb: The error code for exit() calls.
 *@count_flag: Indicates whether to count this line of input.
 *@filename: The filename of the program.
 *@env: Linked list representing a local copy of environ.
 *@environ: ustom modified copy of environ obtained from LL env.
 *@history: The history node.
 *@alias: The alias node.
 *@envir_changed: Indicates whether environ has been modified.
 *@status: The return status of the last executed command.
 *@cmd_buffer: Address of the pointer to cmd_buffer. On if chaining.
 *@cmd_buffer_type:  Type of command buffer (||, &&, ;).
 *@readfiled: The file descriptor from which to read line input.
 *@historycount: The count of history line numbers.
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int count_of_line;
	int error_nb;
	int count_flag;
	char *filename;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int envir_changed;
	int status;

	char **cmd_buffer;
	int cmd_buffer_type;
	int readfiled;
	int historycount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - Holds a string representing a builtin and related function.
 *@type: The flag indicating the builtin command.
 *@func: The function.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shell.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* parse.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void e_puts(char *);
int _eputchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* string_functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string_functions1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* string_fns.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int bfree(void **);

/* functions.c */
int is_interactive(info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int string_integer(char *);

/* errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* shell_functions.c */
int shell_exit(info_t *);
int shell_cd(info_t *);
int shell_help(info_t *);

/* shell_functions1.c */
int my_history(info_t *);
int my_alias(info_t *);

/* getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* info.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* env.c */
char *get_env(info_t *, const char *);
int my_env(info_t *);
int myset_env(info_t *);
int myunset_env(info_t *);
int populate_env_list(info_t *);

/* get_env.c */
char **get_environ(info_t *);
int un_setenv(info_t *, char *);
int set_env(info_t *, char *, char *);

/* gethistory.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* lists_functions.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* lists_functions1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
