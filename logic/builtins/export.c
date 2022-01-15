/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:41:05 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/16 01:17:55 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

static void	print_with_equal_char(char **env, int i, int j)
{
	ft_putchar_fd(env[i][j], STDOUT_FILENO);
	ft_putchar_fd('\"', STDOUT_FILENO);
	j++;
	while (env[i][j])
	{
		ft_putchar_fd(env[i][j], STDOUT_FILENO);
		j++;
	}
	ft_putchar_fd('\"', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	print_export_no_args(t_list_commands *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->env_vars[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (cmd->env_vars[i][j] && cmd->env_vars[i][j] != '=')
		{
			ft_putchar_fd(cmd->env_vars[i][j], STDOUT_FILENO);
			j++;
		}
		if (cmd->env_vars[i][j] == '=')
			print_with_equal_char(cmd->env_vars, i, j);
		else
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

static char	**adding_new_env_var(t_list_commands *cmd)
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

	i = 1;
	only_spaces = 0;
	g_error_code = 0;
	if (cmd->command[1] != NULL && cmd->number > 1)
	{
		if (!check_multiple_spaces(cmd->command))
			print_export_no_args(cmd);
		else
			cmd->env_vars = adding_new_env_var(cmd);
	}
	else if (!cmd->command[1] || cmd->number >= 1)
		print_export_no_args(cmd);
	return ;
}
