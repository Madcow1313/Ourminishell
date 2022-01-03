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

void	errors(void);
void	cd_errors(char *path);
char	**path_directories(t_list_commands *cmd);

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

#endif