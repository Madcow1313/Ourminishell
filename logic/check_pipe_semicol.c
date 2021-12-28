#include "../logic/logic.h"

int	check_pipe_semicol(t_list_commands *cmd)
{
	if (!ft_strncmp(cmd->command[0], ";", ft_strlen(cmd->command[0])))
	{
		g_error_code = 2;
		ft_putstr_fd("bash: ", 2);
		errors();
		return (0);
	}
	else if (!ft_strncmp(cmd->command[0], "|", ft_strlen(cmd->command[0])))
	{
		g_error_code = 2;
		ft_putstr_fd("bash: ", 2);
		errors();
		return (0);
	}
	return (1);
}