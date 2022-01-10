#include "../logic/logic.h"

static void	print_env_vars(char **env)
{
	int	i;

	i = -1;
	while(env[++i])
		ft_putstr_fd(env[i], 1);
}

void	process_env(t_list_commands *cmd)
{
	if (cmd->command[1])
		return ;
	print_env_vars(cmd->env_vars);
}