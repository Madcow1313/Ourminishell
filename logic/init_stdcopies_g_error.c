#include "../logic/logic.h"

void	init_stdcopies_g_error(t_list_commands *cmd)
{
	cmd->stdin_copy = dup(STD_IN);
	cmd->stdout_copy = dup(STD_OUT);
	g_error_code = 0;
}