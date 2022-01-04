#include "../logic/logic.h"

void	print_export_no_args(t_list_commands *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->env_vars[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while(cmd->env_vars[i][j] != '=')
		{
			ft_putchar_fd(cmd->env_vars[i][j], 1);
			j++;
		}
		ft_putchar_fd(cmd->env_vars[i][j], 1);
		ft_putchar_fd('\"', 1);
		j++;
		while(cmd->env_vars[i][j])
		{
			ft_putchar_fd(cmd->env_vars[i][j], 1);
			j++;
		}
		ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	adding_new_env_var(t_list_commands *cmd)
{
	char	**new_env;

	new_env = check_valid_envp(cmd);
	if (new_env == NULL)
		return ;
 	int	i = 0;
	while(new_env[i])
	{
		printf("%s\n", new_env[i]);
		i++;
	}
	//check_replace_env(cmd);
}

void	process_export(t_list_commands *cmd)
{
	int	i = 0;
	while(cmd->command[i])
	{
		printf("%s\n", cmd->command[i]);
		i++;
	}
	if (cmd->command[1] == NULL)
		print_export_no_args(cmd);
	else
		adding_new_env_var(cmd);
}