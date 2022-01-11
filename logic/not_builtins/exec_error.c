#include "../logic/logic.h"

void	exec_error(t_list_commands *cmd, char *file_path)
{
	if (file_path)
		free(file_path);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(cmd->command[0], 2);
	ft_putstr_fd(" ", 2);
	errors();
}
