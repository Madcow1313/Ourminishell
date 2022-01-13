#include "../logic/logic.h"

static void	print_env_vars(char **env)
{
	int	i;

	i = -1;
	while(env[++i])
		if (env[i])
			ft_putendl_fd(env[i], 1);
}

void	process_env(t_list_commands *cmd)
{
	print_env_vars(cmd->env_vars);
	g_error_code = 0;
}
