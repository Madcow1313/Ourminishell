#include "../logic/logic.h"

void	echo_without_newline(t_list_commands *cmd)
{
	(void)cmd;
	write(1, "echo without newline", 20);
}

void	echo_with_newline(t_list_commands *cmd)
{
	int	i;
	int	j;

	i = 1;
	while(cmd->command[i])
	{
		j = 0;
		while (cmd->command[i][j])
		{
			if (cmd->command[i][0] == ' ')
				j++;
			ft_putchar_fd(cmd->command[i][j], 1);
			//write(1, &(cmd->command[i][j]), 1);
			j++;
		}
		ft_putchar_fd(' ', 1);
		//write(1, " ", 1);
		i++;
	}
	write (1, "\n", 1);
	return ;
}

void	process_echo(t_list_commands *cmd)
{
	if (cmd->command[1] != NULL)
	{
		if (!ft_strncmp(cmd->command[1], "-n", ft_strlen("-n")))
			echo_without_newline(cmd);
		else
			echo_with_newline(cmd);
	}
	else
		write(1, "\n", 1);
	return ;
}

void	builtins(t_list_commands *cmd)
{
	if (!ft_strncmp(cmd->command[0], "echo", ft_strlen("echo")))
		process_echo(cmd);
/* 	else if (!ft_strncmp(cmd->command[0], "cd", ft_strlen("cd")))
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
		process_exit(cmd); */
}