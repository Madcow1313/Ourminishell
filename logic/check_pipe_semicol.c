#include "../logic/logic.h"

int	check_pipe_semicol(t_list_commands *cmd)
{
	if (!ft_strcmp(cmd->command[0], ";"))
	{
		g_error_code = 2;
		ft_putstr_fd("bash: syntax error near unexpected token ';'\n", STD_ERROR);
		return (0);
	}
	else if (!ft_strcmp(cmd->command[0], "|"))
	{
		g_error_code = 2;
		ft_putstr_fd("bash: syntax error near unexpected token '|'\n", STD_ERROR);
		return (0);
	}
	return (1);
}
