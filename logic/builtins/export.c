#include "../logic/logic.h"

void	print_with_equal_char(char **env, int i, int j)
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

void print_export_no_args(t_list_commands *cmd)
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
	char **new_env;
	int env_len;

	new_env = check_valid_envp(cmd);
	if (new_env == NULL)
		return (cmd->env_vars);
	env_len = count_env_len(new_env);
	/* int i = -1;
	while (new_env[++i])
		printf("%s\n", new_env[i]); */
	cmd->env_vars = check_replace_env(cmd->env_vars, new_env, env_len);
	// int i = -1;
	// while (cmd->env_vars[++i])
	// 	printf("%s\n", cmd->env_vars[i]);
	return (cmd->env_vars);
}

void process_export(t_list_commands *cmd)
{
	if (cmd->command[1] == NULL)
		print_export_no_args(cmd);
	else
		cmd->env_vars = adding_new_env_var(cmd);
}