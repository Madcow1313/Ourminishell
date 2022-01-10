#include "../logic/logic.h"

static void	print_with_equal_char(char **env, int i, int j)
{
	ft_putchar_fd(env[i][j], 1);
	ft_putchar_fd('\"', 1);
	j++;
	while (env[i][j])
	{
		ft_putchar_fd(env[i][j], 1);
		j++;
	}
	ft_putchar_fd('\"', 1);
	ft_putchar_fd('\n', 1);
}

static void print_export_no_args(t_list_commands *cmd)
{
	int i;
	int j;

	i = 0;
	while (cmd->env_vars[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (cmd->env_vars[i][j] && cmd->env_vars[i][j] != '=')
		{
			ft_putchar_fd(cmd->env_vars[i][j], 1);
			j++;
		}
		if (cmd->env_vars[i][j] == '=')
			print_with_equal_char(cmd->env_vars, i, j);
		else
			ft_putchar_fd('\n', 1);
		i++;
	}
}

static char **adding_new_env_var(t_list_commands *cmd)
{
	char	**new_env;
	int		new_len;
	int		i;

	i = -1;
	new_env = check_valid_envp(cmd);
	if (new_env == NULL) 
		return (cmd->env_vars);
	// for (int j = 1; new_env[j]; j++)
	// 	printf("new_env[j] = %s\n", new_env[j]);
	new_len = count_env_len(new_env);
	cmd->env_vars = check_replace_env(cmd->env_vars, new_env, new_len);
	while(++i <= new_len + 1)
		if (new_env[i])
			free(new_env[i]);
	return (cmd->env_vars);
}

void process_export(t_list_commands *cmd)
{
	// for (int i = 1; cmd->command[i]; i++)
	// 	printf("%s\n", cmd->command[i]);
	//printf("Hello\n");
	if (cmd->command[1])
		cmd->env_vars = adding_new_env_var(cmd);
	else
		print_export_no_args(cmd);
	//printf("No free error\n");
}