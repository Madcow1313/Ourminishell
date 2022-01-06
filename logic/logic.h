#ifndef LOGIC_H

# define LOGIC_H

#include "../simple_parser/parser.h"
#include "../logic/libft/libft.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <dirent.h>
#include <limits.h>

//updated func will write info about the process into a struct
typedef struct s_subprocess
{
	pid_t pid;
	int stdin;
	int stdout;
	int stderr;
}				t_subprocess;

char	**free_array(char **new_env);
int		check_first_symbol(char c);
int		wrong_symbols(char *str);

void	errors(void);
void	cd_errors(char *path);
void	export_errors(char *str);
void	malloc_error(char **s);


void	start_cmd(t_list_commands *cmd, t_command *p);
void	single_command(t_list_commands *cmd);
int		check_pipe_semicol(t_list_commands *cmd);

void	builtins(t_list_commands *cmd);

//single echo with redirs
void	process_echo(t_list_commands *cmd);
void	redirects(t_list_commands *cmd, int nl);

//single cd's
void	process_cd(t_list_commands *cmd);
void	set_pwd(t_list_commands *cmd);
char	**find_old_pwd(t_list_commands *cmd);

//single pwd
void	process_pwd(t_list_commands *cmd);

//single export
void	process_export(t_list_commands *cmd);
char	**check_valid_envp(t_list_commands *cmd);
int	count_env_len(char **env);
char	**check_replace_env(char **old_env, char **new_env, int len);

//single exit
void	process_exit(char **args);

#endif