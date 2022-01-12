#include "../logic/logic.h"

static void	print_env_vars(char **env)
{
	int	i;

	i = -1;
	while(env[++i])
		if (env[i])
			ft_putendl_fd(env[i], 1);
}

/* static int	check_env_cmd(t_list_commands *cmd)
{
	int	i;

	i = 1;
	while(cmd->command[i])
	{
		if (!check_only_space(cmd->command[i]))
			i++;
		else
			return (0);
	}
	return (1);
} */

void	process_env(t_list_commands *cmd)
{
	// if (cmd->command[1])
	// {
	// 	if (!check_env_cmd(cmd))
	// 		return ;
	// 	else
	// 		print_env_vars(cmd->env_vars);
	// 	g_error_code = 0;
	// 	return ;
	// }
	printf("hello\n");
	print_env_vars(cmd->env_vars);
	g_error_code = 0;
}