#include "../logic/logic.h"

void	single_command(t_list_commands *cmd)
{
	t_opendir	open_dir;

	//for(int i = 0; cmd->command[i]; i++)
		//printf("single command %s\n", cmd->command[i]);
	if (!ft_strcmp(cmd->command[0], "echo"))
		process_echo(cmd);
 	else if (!ft_strcmp(cmd->command[0], "cd"))
		process_cd(cmd);
	else if (!ft_strcmp(cmd->command[0], "pwd"))
	 	process_pwd(cmd);
	else if (!ft_strcmp(cmd->command[0], "export"))
		process_export(cmd);
	else if (!ft_strcmp(cmd->command[0], "unset"))
		process_unset(cmd);
	else if(!ft_strcmp(cmd->command[0], "env"))
		process_env(cmd);
	else if (!ft_strcmp(cmd->command[0], "exit"))
		process_exit(cmd->command + 1);
	else
		exec(cmd, &open_dir);
	return ;
}
