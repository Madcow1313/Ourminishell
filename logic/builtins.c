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

int	check_pipes(t_list_commands *cmd)
{
	int	i;

	i = 1;
	while(cmd->command[i])
	{
		if (!ft_strncmp(cmd->command[i], "|", ft_strlen(cmd->command[i])))
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
	cmd->pipe_right = 0;
/* 	if (cmd->type[0] == BUILT_IN)
		check_builtins(cmd);
	else if (cmd->type[0] == COMMAND)
		check_command();
	else if (cmd->type[0] == ENVIRONMENT_VAR)
		check_env_var();
	else if (cmd->type[0] == WORD)
		check_word();
	else if (cmd->type[0] == REDIRECT_LEFT
			|| cmd->type[0] == REDIRECT_RIGHT)
				check_redirect();
	else if (cmd->type[0] == REDIRECT_AND_APPEND)
		check_redir_and_append();
	else if (cmd->type[0] == HERE_DOC)
		check_here_doc(); */
	if (!check_pipe_semicol(cmd))
		return ;
	//if (!check_pipes)
	
}

void	start_cmd(t_list_commands *cmd)
{	
	ft_s_h();

	check_start_cmd(cmd);
	return ;
}