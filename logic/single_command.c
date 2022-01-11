#include "../logic/logic.h"

void	single_command(t_list_commands *cmd)
{
	t_opendir	open_dir;

	printf("%s\n", cmd->command[0]);
	if (cmd->type[0] == BUILT_IN)
		builtins(cmd, &open_dir);
	else
		exec(cmd, &open_dir);
	// else if (cmd->type[0] == REDIRECT_LEFT
	// 		|| cmd->type[0] == REDIRECT_RIGHT)
	// 	redirect();
	// else if (cmd->type[0] == REDIRECT_AND_APPEND)
	// 	redir_and_append();
	// else if (cmd->type[0] == HERE_DOC)
	// 	here_doc();
	return ;
}
