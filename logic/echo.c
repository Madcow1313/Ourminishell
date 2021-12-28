#include "../logic/logic.h"

void	echo_without_newline(t_list_commands *cmd)
{
	int	i;
	int	j;

	i = 2;
	while(cmd->command[i])
	{
		j = 0;
		while (cmd->command[i][j])
		{
			write(1, &(cmd->command[i][j]), 1);
			j++;
		}
		if (cmd->command[i + 1])
			write(1, " ", 1);
		i++;
	}
	return ;
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
			write(1, &(cmd->command[i][j]), 1);
			j++;
		}
		if (cmd->command[i + 1])
			write(1, " ", 1);
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
