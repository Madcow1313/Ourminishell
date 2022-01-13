#include "../logic/logic.h"

void	process_only_redirects(t_list_commands * cmd)
{
	write(cmd->fd[1], "\n", 1);
}