#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#define SINGLE_QM 1
#define DOUBLE_QM 2
#define	PIPE 3
#define BUILT_IN 4
#define	REDIRECT_RIGHT 5
#define REDIRECT_LEFT 6
#define READ_INPUT 7
#define REDIRECT_AND_APPEND 8
#define ENVIRONMENT_VAR 9
#define SEMICOLON 10
#define	WORD 11
#define COMMAND 12

typedef struct s_command
{
	const char *word;
	size_t len;
} t_command;

typedef struct s_list_commands
{
	char **command;
	int	*type;
	int number;
} t_list_commands;

/*some libft utils*/
size_t ft_strlen(const char *string);
size_t	ft_strlcpy (char *dst, const char *src, size_t size);
int	ft_strchr(const char *string, int symbol);


/*parser functions*/
t_command	*get_full_command(const char *string, t_command *command);
t_list_commands	*start_parse(t_command *command, t_list_commands *list);
int	handle_quotes(t_list_commands *list, t_command *command, int character, size_t *i);
int	handle_redirects(t_list_commands *list, int character, size_t *i);


/*structure functions*/
int	prepare_list(t_list_commands *list, t_command *command);

/*delete this*/
void	print_commands_and_words(t_list_commands *list);
#endif
