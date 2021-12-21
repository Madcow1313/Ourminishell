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

void	check_start_cmd(t_list_commands *cmd)
{
	/* if (cmd->type[0] == BUILT_IN)
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
		check_here_doc();
	else
	 */	check_quotes_pipe_semicol(cmd);
}

void	start_cmd(t_list_commands *cmd)
{	
	ft_s_h();

	check_start_cmd(cmd);
	return ;
}