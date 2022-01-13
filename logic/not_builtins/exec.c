#include "../logic/logic.h"

void	exec(t_list_commands *cmd, t_opendir *open_dir)
{
	pid_t	pid;
	char	*file_path;

	write(1, "hree\n", 5);
	file_path = get_binary_from_path(cmd, open_dir);
	if (file_path)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(file_path, cmd->command, cmd->env_vars) == -1)
			{
				g_error_code = errno;
				exec_error(cmd, file_path);
				return ;
			}
			g_error_code = 0;
		}
		else if (pid > 0)
			wait(&pid);
		else
			ft_putstr_fd("Can't execute command, fork failed\n", STD_ERROR);
	}
	else
		command_error(cmd->command[0]);
	if (file_path)
		free(file_path);
}
