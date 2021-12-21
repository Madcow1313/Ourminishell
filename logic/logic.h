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

void	start_cmd(t_list_commands *cmd);
void	check_quotes_pipe_semicol(t_list_commands *cmd);

char	*process_echo(t_list_commands *cmd, char *rez);
void	check_echo(char *str, t_list_commands *cmd);

#endif