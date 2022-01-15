/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:41:05 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/15 18:43:14 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	i;
	int	j;

	i = 0;
	printf("Sega here\n");
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
	ft_putstr_fd("No sega 0\n", 1);
	if (cmd->command[1] != NULL && cmd->number > 1)
	{
		//ft_putstr_fd(cmd->command[1], 1);
		ft_putstr_fd("No sega in spaces\n", 1);
		if (!check_multiple_spaces(cmd->command))
			print_export_no_args(cmd);
		else
			cmd->env_vars = adding_new_env_var(cmd);
		ft_putstr_fd("No sega in spaces2\n", 1);
	}
	else if (!cmd->command[1] || cmd->number == 1)
		{ft_putstr_fd("No sega here\n", 1); print_export_no_args(cmd); ft_putstr_fd("No sega here2\n", 1);}
	return ;
	// if (!cmd->command[1])
	// {	print_export_no_args(cmd);
	// 	printf("All good - export\n");}
	// else if (cmd->command[1] != NULL)
	// {
	// 	while (cmd->command[++i])
	// 	{
	// 		if (check_only_space(cmd->command[i]))
	// 			only_spaces++;
	// 	}
	// 	if (only_spaces == 0)
	// 		print_export_no_args(cmd);
	// }
	// else //if (cmd->command[1]) //check cmd for duplicates, where i'll count len without duples and in filling new_env i'll skip same str???
	// 	cmd->env_vars = adding_new_env_var(cmd);
	//else
	//	print_export_no_args(cmd);
}
