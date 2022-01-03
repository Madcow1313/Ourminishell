#include "../logic/logic.h"

int	check_pipe_semicol(t_list_commands *cmd)
{
	if (!ft_strncmp(cmd->command[0], ";", ft_strlen(";")))
	{
		g_error_code = 2;
		ft_putstr_fd("bash: syntax error near unexpected token ';'\n", 2);
		return (0);
	}
	else if (!ft_strncmp(cmd->command[0], "|", ft_strlen("|")))
	{
		g_error_code = 2;
		ft_putstr_fd("bash: syntax error near unexpected token '|'\n", 2);
		return (0);
	}
	return (1);
}
