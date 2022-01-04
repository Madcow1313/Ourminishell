#include "../logic/logic.h"

void	builtins(t_list_commands *cmd)
{
	int i = 0;
	while (cmd->command[i])
	{
		printf("%s\n", cmd->command[i]);
		i++;
	}
	if (!ft_strncmp(cmd->command[0], "echo", ft_strlen("echo")))
		process_echo(cmd);
 	else if (!ft_strncmp(cmd->command[0], "cd", ft_strlen("cd")))
		process_cd(cmd);
	else if (!ft_strncmp(cmd->command[0], "pwd", ft_strlen("pwd")))
	 	process_pwd(cmd);
	else if (!ft_strncmp(cmd->command[0], "export", ft_strlen("export")))
	 	process_export(cmd);
	// else if (!ft_strncmp(cmd->command[0], "unset", ft_strlen("unset")))
	// 	process_unset(cmd);
	// else if(!ft_strncmp(cmd->command[0], "env", ft_strlen("env")))
	// 	process_env(cmd);
	// else if (!ft_strncmp(cmd->command[0], "exit", ft_strlen("exit")))
	// 	process_exit(cmd);
	return ;
}
