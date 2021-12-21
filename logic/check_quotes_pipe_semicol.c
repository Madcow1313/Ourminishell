#include "../logic/logic.h"

void	check_quotes_pipe_semicol(t_list_commands *cmd)
{
	if (!ft_strncmp(cmd->command[0], ";", ft_strlen(cmd->command[0])))
	{
		error_code = 2;
		errors();
	}
	else if (!ft_strncmp(cmd->command[0], "|", ft_strlen("|")))
	{
		error_code = 2;
		errors();
	}
	return ;
}