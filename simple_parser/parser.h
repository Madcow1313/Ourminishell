#ifndef PARSER_H
# define PARSER_H

# include "readline/readline.h"
# include <readline/history.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>

# define SINGLE_QM 1
# define DOUBLE_QM 2
# define PIPE 3
# define BUILT_IN 4
# define REDIRECT_RIGHT 5
# define REDIRECT_LEFT 6
# define HERE_DOC 7
# define REDIRECT_AND_APPEND 8
# define ENVIRONMENT_VAR 9
# define SEMICOLON 10
# define WORD 11
# define COMMAND 12
# define ABSOLUTE_PATH 13
# define RELATIVE_PATH 14
# define SEP_SPACE 15

int	g_error_code;

typedef struct s_command
{
	const char *word;
	size_t len;
} t_command;

typedef struct s_list_commands
{
	char		**command;
	char		**env_vars;
	int			*type;
	t_command	*p;
	int			number;
	int			fd[2];
	int			stdin_copy;
	int			stdout_copy;
	int			pipe_right;
	int			pipe_left;
	int			semicol;
	int			heredoc;
	int			old_stdout;
	int			old_stdin;
} 			t_list_commands;

int	ft_s_h(void);
void	ft_s_h_heredoc(void);

void	print_shit();
/*some libft utils*/
char	*ft_strnstr (const char *big, const char *little, size_t len);
size_t ft_strlen(const char *string);
size_t	ft_strlcpy (char *dst, const char *src, size_t size);
int	ft_strchr_parser(const char *string, int symbol);
int	ft_strncmp(const char *string1, const char *string2, size_t num);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strchr_for_dq(const char *string, int symbol);

/*parser functions
change abs and relative path, they are doing the same*/
t_command	*get_full_command(const char *string, t_command *command);
t_list_commands	*start_parse(t_command *command, t_list_commands *list);
int	handle_quotes(t_list_commands *list, t_command *command, int character, size_t *i);
int	handle_redirects(t_list_commands *list, int character, size_t *i);
size_t	find_first_qm(const char *string);
char	*get_env_var_value(char **env_vars, char *string);
int	delete_quotes(t_list_commands *list);
char *get_prefix_for_env(char **env_vars, char *string);

/*structure functions*/
int	prepare_list(t_list_commands *list, t_command *command);

/*delete this*/
void	print_commands_and_words(t_list_commands *list);

/*some redirect functions*/
int	get_here_doc(char *end, t_list_commands *list);
int	get_redirect_type(t_list_commands *list);
int	rid_of_redirect_right(t_list_commands *list);
void	set_default_fd(t_list_commands *list);

void		rl_replace_line(const char *text, int clear_undo);

/*shitty fucntion to make it more good loking*/
char	**get_normal_array(t_list_commands *list);
char **get_no_space(t_list_commands *list);
#endif
