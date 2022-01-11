#include "../logic/logic.h"

void	single_command(t_list_commands *cmd)
{
	t_opendir	open_dir;

	//for(int i = 0; cmd->command[i]; i++)
	//	printf("single command %s\n", cmd->command[i]);
	if (!ft_strncmp(cmd->command[0], "echo", ft_strlen("echo")))
		process_echo(cmd);
 	else if (!ft_strncmp(cmd->command[0], "cd", ft_strlen("cd")))
		process_cd(cmd);
	else if (!ft_strncmp(cmd->command[0], "pwd", ft_strlen("pwd")))
	 	process_pwd(cmd);
	else if (!ft_strncmp(cmd->command[0], "export", ft_strlen("export")))
		process_export(cmd);
	else if (!ft_strncmp(cmd->command[0], "unset", ft_strlen("unset")))
		process_unset(cmd);
	else if(!ft_strncmp(cmd->command[0], "env", ft_strlen("env")))
		process_env(cmd);
	else if (!ft_strncmp(cmd->command[0], "exit", ft_strlen("exit")))
		process_exit(&cmd->command[1]);
	else
		exec(cmd, &open_dir);
	return ;
}
