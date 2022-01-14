#include "../logic/logic.h"

void	free_cmd(t_list_commands *cmd)
{
	size_t	i;

	i = -1;
	if (cmd->command)
	{
		while(cmd->command[++i])
			free(cmd->command[i]);
	}
	free(cmd->command);
	cmd->command = NULL;
	i = -1;
	if (cmd->type)
		free(cmd->type);
}

int	count_pipes(t_list_commands *cmd)
{
	int	i;
	int	count;

	count = 0;
	i = 1;
	while(cmd->command[i])
	{
		if (cmd->command[i] && !ft_strcmp(cmd->command[i], "|"))
			count++;
		i++;
	}
	if (count > 0)
		return (1);
	else
		return (0);
}

void	check_start_cmd(t_list_commands *cmd)
{	
	if (cmd->command[0] == NULL || !cmd->command)
		return ;
	if (!check_pipe_semicol(cmd))
		return ;
	if (cmd->pipe_right == -1
		&& cmd->pipe_left == -1)
		single_command(cmd);
	else
		cmd_with_pipes(cmd);
	return ;
}

void	start_cmd(t_list_commands *cmd)
{	
	ft_s_h();

	check_start_cmd(cmd);
	printf("All good here\n");
	//free_cmd(cmd);
	return ;
}