#include "../logic/logic.h"

static void	redirect_with_nl(t_list_commands *cmd, int j)
{
		if (cmd->command[j] == NULL)
			return ;
		while (cmd->command[j])
		{
			write(cmd->fd[1], cmd->command[j], ft_strlen(cmd->command[j]));
			if (cmd->command[j + 1] != NULL)
				write(cmd->fd[1], " ", 1);
			j++;
		}
		write (cmd->fd[1], "\n", 1);
}

void	redirects(t_list_commands *cmd, int nl)
{
	int	j;

	j = 1;
	if (nl == 0)
	{
		if (cmd->command[2] != NULL)
		{
			while (cmd->command[++j])
			{
				write(cmd->fd[1], cmd->command[j], ft_strlen(cmd->command[j]));
				if (cmd->command[j + 1] != NULL)
					write(cmd->fd[1], " ", 1);
			}
		}
		return ;
	}
	else if (nl == 1)
		redirect_with_nl(cmd, j);
}
