#include "../logic/logic.h"

/* static void	free_cmd(t_list_commands *cmd)
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
} */

int	count_pipes(t_list_commands *cmd)
{
	int	i;

	i = 1;
	while(cmd->command[i])
	{
		if (cmd->command[i] && !ft_strncmp(cmd->command[i], "|", ft_strlen("|")))
			cmd->pipe_right++;
		i++;
	}
	if (cmd->pipe_right > 0)
		return (1);
	else
		return (0);
}

void	check_start_cmd(t_list_commands *cmd)
{	
	if (cmd->command[0] == NULL)
		return ;
	if (!check_pipe_semicol(cmd))
		return ;
	if (!count_pipes(cmd))
		single_command(cmd);
	//printf("No free error\n");
	//else
		//cmd_with_pipe(cmd);
	return ;
}

void	start_cmd(t_list_commands *cmd, t_command *p)
{	
	cmd->p = p;
	cmd->pipe_right = 0;

	ft_s_h();

	//printf("%d\n", cmd->type[0]);
	//printf("%s\n", cmd->command[0]);
	check_start_cmd(cmd);
	//printf("No free error\n");
	//free_cmd(cmd);
	return ;
}