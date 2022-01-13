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

static void	print_export_no_args(t_list_commands *cmd)
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

	new_env = check_valid_envp(cmd);
	if (new_env == NULL) 
		return (cmd->env_vars);
	new_len = count_env_len(new_env);
	check_duplicates(new_env, new_len);
	cmd->env_vars = check_replace_env(cmd->env_vars, new_env, new_len);
	free(new_env);
	return (cmd->env_vars);
}

void	process_export(t_list_commands *cmd)
{
	int	i;
	int	only_spaces;

	i = 0;
	only_spaces = 0;
	g_error_code = 0;
	while (cmd->command[++i])
		if (check_only_space(cmd->command[i]))
			only_spaces++;
	if (only_spaces == 0)
		print_export_no_args(cmd);
	else if (cmd->command[1]) //check cmd for duplicates, where i'll count len without duples and in filling new_env i'll skip same str???
		cmd->env_vars = adding_new_env_var(cmd);
	else
		print_export_no_args(cmd);
}
