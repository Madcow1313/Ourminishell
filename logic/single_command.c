#include "../logic/logic.h"

void	single_command(t_list_commands *cmd)
{
	//printf("%d\n", cmd->type[0]);
	if (cmd->type[0] == BUILT_IN)
		builtins(cmd);
/* 	else if (cmd->type[0] == COMMAND)
		command();
	else if (cmd->type[0] == ENVIRONMENT_VAR)
		env_var();
	else if (cmd->type[0] == WORD)
		word();
	else if (cmd->type[0] == REDIRECT_LEFT
			|| cmd->type[0] == REDIRECT_RIGHT)
		redirect();
	else if (cmd->type[0] == REDIRECT_AND_APPEND)
		redir_and_append();
	else if (cmd->type[0] == HERE_DOC)
		here_doc(); */
	//printf("No free error\n");
	return ;
}
