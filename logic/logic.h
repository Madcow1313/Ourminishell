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
#include <stdbool.h>

# define STD_IN 0
# define STD_OUT 1
# define STD_ERROR 2

/*structure for finding binaries in PATH*/
typedef struct s_opendir
{
	char			**path;
	DIR				*dir;
	int				i;
	struct dirent	*name;
	char			*file_path;
}				t_opendir;

char	**free_array(char **env);
int		check_first_symbol(char c);
int		wrong_symbols(char *str);
bool	is_numeric(char *str);

//errors func

void	errors(void);
void	cd_errors(char *path);
void	export_errors(char *str);
void	malloc_error(char **s);
void	command_error();
void	exec_error(t_list_commands *cmd, char *file_path);

//starting shell func

void	start_cmd(t_list_commands *cmd, t_command *p);
void	single_command(t_list_commands *cmd);
int		check_pipe_semicol(t_list_commands *cmd);

//single echo with redirs
void	process_echo(t_list_commands *cmd);
void	redirects(t_list_commands *cmd, int nl);

//single cd's
void	process_cd(t_list_commands *cmd);
void	set_pwd(t_list_commands *cmd);
char	**find_old_pwd(t_list_commands *cmd);
int	cmpr_oldpwd(t_list_commands *cmd, int i);
int	cmpr_pwd(t_list_commands *cmd, int i);

//single pwd
void	process_pwd(t_list_commands *cmd);

//single export
void	process_export(t_list_commands *cmd);
char	**check_valid_envp(t_list_commands *cmd);
int		check_only_space(char *s);
char	**init_new_env(int len);
char	**alloc_and_fill_new_env(t_list_commands *cmd, char **new_env);
int		count_env_len(char **env);
char	**check_replace_env(char **old_env, char **new_env, int len);

//single exit
void	process_exit(char **args);

//single unset
void	process_unset(t_list_commands *cmd);
char	**check_valid_unset(t_list_commands *cmd);

//single env
void	process_env(t_list_commands *cmd);

void	exec(t_list_commands *cmd, t_opendir *open_dir);
char	*get_binary_from_path(t_list_commands *cmd, t_opendir *o_dir);
int	ft_cmprcmd(const char *string1, const char *string2);

//pipes
void	cmd_with_pipes(t_list_commands *cmd);
bool	our_builtin(char *command);
int	ft_strcmp(const char *s1, const char *s2);
void	manage_out_pipe(t_list_commands *cmd);
void	manage_in_pipe(t_list_commands *cmd);

#endif