#include "../logic/logic.h"

void	process_pwd(t_list_commands *cmd)
{
	char	*pwd;

	if(cmd->command[1] != NULL)
	{
		if (!ft_strncmp(cmd->command[1], "-", ft_strlen("-")))
		{
			g_error_code = 2;
			ft_putstr_fd("bash: pwd: -", cmd->fd[1]);
			ft_putchar_fd(cmd->command[1][1], cmd->fd[1]);
			ft_putstr_fd(": invalid option\n", cmd->fd[1]);
			return ;
		}
	}
	//pwd = get_env_var_value(cmd->env_vars, "PWD");
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, cmd->fd[1]);
	return ;
}
