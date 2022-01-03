#include "../logic/logic.h"

int	check_redir(t_list_commands *cmd, int nl)
{
	size_t	i;

	i = 0;
	while (i < cmd->p->len)
	{
		if (cmd->type[i] == REDIRECT_RIGHT ||
			cmd->type[i] == REDIRECT_AND_APPEND)
		{
			redirects(cmd, nl);
			return (0);
		}
		i++;
	}
	return (1);
}

void	echo_without_newline(t_list_commands *cmd)
{
	int	i;
	int	j;

	i = 2;
	if (!check_redir(cmd, 0))
		return ;
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
	if (!check_redir(cmd, 1))
		return ;
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
