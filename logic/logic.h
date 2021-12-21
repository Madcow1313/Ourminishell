#ifndef LOGIC_H

# define LOGIC_H

#include "../simple_parser/parser.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <dirent.h>

//updated func will write info about the process into a struct
typedef struct s_subprocess
{
	pid_t pid;
	int stdin;
	int stdout;
	int stderr;
}				t_subprocess;

void	start_cmd(t_list_commands *cmd);
void	check_echo(char *str, t_list_commands *cmd);

#endif