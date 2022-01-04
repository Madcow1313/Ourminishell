#include "../logic/logic.h"

char	**path_directories(t_list_commands *cmd)
{
	int	i;
	char	**path;

	i = 0;
	while (ft_strncmp(cmd->env_vars[i], "PATH", ft_strlen("PATH")))
		i++;
	path = ft_split(cmd->command[i], ':');
	return (path);
}

int	count_pipes_and_semicol(t_list_commands *cmd)
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
	if (!count_pipes_and_semicol(cmd))
		single_command(cmd);
	//else
		//cmd_with_pipe(cmd);
	return ;
}

void	start_cmd(t_list_commands *cmd, t_command *p)
{	
	cmd->p = p;
	cmd->pipe_right = 0;

	ft_s_h();

	check_start_cmd(cmd);
	return ;
}