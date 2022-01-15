/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:49:58 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/16 02:24:24 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGIC_H

# define LOGIC_H

# include "../simple_parser/parser.h"
# include "../logic/libft/libft.h"
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <stdint.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <dirent.h>
# include <limits.h>
# include <stdbool.h>

# define STD_IN 0
# define STD_OUT 1
# define STD_ERROR 2
# define TRUE 1
# define FALSE 0

/*structure for finding binaries in PATH*/

typedef struct s_opendir
{
	char			**path;
	DIR				*dir;
	int				i;
	struct dirent	*name;
	char			*file_path;
}				t_opendir;

void	free_cmd(t_list_commands *cmd);
char	**free_array(char **env);
int		check_first_symbol(char c);
int		wrong_symbols(char *str);
int		is_numeric(char *str);
void	init_stdcopies_g_error(t_list_commands *cmd, t_command *p);

//errors func

void	errors(void);
void	cd_errors(char *path);
void	export_errors(char *str);
void	malloc_error(char **s);
void	command_error(char *s);
void	exec_error(t_list_commands *cmd);
int		puterror_exec(char *s1, char *s2, char *s3, int code);

//starting shell func

void	start_cmd(t_list_commands *cmd);
void	single_command(t_list_commands *cmd, t_opendir *o_dir);
int		check_pipe_semicol(t_list_commands *cmd);

//echo with redirs

void	process_echo(t_list_commands *cmd);
void	redirects(t_list_commands *cmd, int nl);

//cd's

void	process_cd(t_list_commands *cmd);
void	set_pwd(t_list_commands *cmd);
char	**find_old_pwd(t_list_commands *cmd);
int		cmpr_oldpwd(t_list_commands *cmd, int i);
int		cmpr_pwd(t_list_commands *cmd, int i);

//pwd

void	process_pwd(t_list_commands *cmd);

//export

void	process_export(t_list_commands *cmd);
char	**check_valid_envp(t_list_commands *cmd);
int		check_only_space(char *s);
int		check_multiple_spaces(char **s);
char	**init_new_env(int len);
char	**alloc_and_fill_new_env(t_list_commands *cmd, char **new_env);
int		count_env_len(char **env);
void	check_duplicates(char **new_env, int new_len);
char	**check_replace_env(char **old_env, char **new_env, int len);
void	parts_to_compare(char **old_env, char **new_env, int k);

//exit

void	process_exit(char **args);

//unset

void	process_unset(t_list_commands *cmd);
char	**check_valid_unset(t_list_commands *cmd);
int		ft_len_after(char **env, int old_len);
char	**fill_unset(char **old, int old_len, int final_len);

//env

void	process_env(t_list_commands *cmd);

void	exec(t_list_commands *cmd, t_opendir *open_dir);
char	*get_binary_from_path(t_list_commands *cmd, t_opendir *o_dir);
int		ft_cmprcmd(const char *string1, const char *string2);

//pipes

void	cmd_with_pipes(t_list_commands *cmd, t_opendir *o_dir);
int		our_builtin(char *command);

//int	
void	manage_out_pipe(t_list_commands *cmd);
void	manage_in_pipe(t_list_commands *cmd);

void	process_only_redirects(t_list_commands *cmd);

//exec

int		is_command_executable(t_list_commands *cmd);

#endif