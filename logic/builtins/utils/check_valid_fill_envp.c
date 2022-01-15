/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_fill_envp.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:26:17 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/16 01:25:39 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

char	**init_new_env(int len)
{
	char	**new_env;

	if (!len)
		return (NULL);
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		malloc_error(new_env);
	return (new_env);
}

char	**alloc_and_fill_new_env(t_list_commands *cmd, char **new_env)
{
	int	i;
	int	id;

	i = 0;
	id = 0;
	while (cmd->command[++i])
	{
		if (!check_first_symbol(cmd->command[i][0])
			|| !wrong_symbols(cmd->command[i])
			|| !check_only_space(cmd->command[i]))
			continue ;
		new_env[id] = cmd->command[i];
		id++;
	}
	new_env[id] = NULL;
	return (new_env);
}

static char	**return_new_env(int len, t_list_commands *cmd)
{
	char	**new_env;

	new_env = init_new_env(len);
	if (!new_env)
		return (NULL);
	new_env = alloc_and_fill_new_env(cmd, new_env);
	return (new_env);
}

char	**check_valid_envp(t_list_commands *cmd)
{
	int		i;
	int		len;

	i = 1;
	len = 0;
	while (cmd->command[i])
	{
		if (!check_first_symbol(cmd->command[i][0])
			|| !wrong_symbols(cmd->command[i]))
		{
			export_errors(cmd->command[i]);
			i++;
			continue ;
		}
		if (!check_only_space(cmd->command[i]))
		{
			i++;
			continue ;
		}
		i++;
		len++;
	}
	return (return_new_env(len, cmd));
}
