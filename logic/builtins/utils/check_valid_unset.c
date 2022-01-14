/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:30:14 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:30:14 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

static int	find_equal_sign(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			return (0);
	}
	return (1);
}

static char	**alloc_unset_arr(t_list_commands *cmd, char **new_env)
{
	int	i;
	int	id;

	i = 0;
	id = 0;
	while (cmd->command[++i])
	{
		if (!check_first_symbol(cmd->command[i][0])
			|| !find_equal_sign(cmd->command[i])
			|| !wrong_symbols(cmd->command[i]))
			continue ;
		new_env[id] = cmd->command[i];
		//if (!new_env[id])
		// {	
		// 	malloc_error(new_env);
		// 	return (new_env);
		// }
		id++;
	}
	new_env[id] = NULL;
	return (new_env);
}

static char	**return_unset_env(int len, t_list_commands *cmd)
{
	char	**new_env;

	new_env = init_new_env(len);
	if (!new_env)
		return (NULL);
	new_env = alloc_unset_arr(cmd, new_env);
	return (new_env);
}

char	**check_valid_unset(t_list_commands *cmd)
{
	int		i;
	int		len;

	i = 1;
	len = 0;
	while (cmd->command[i])
	{
		if (!check_first_symbol(cmd->command[i][0])
			|| !find_equal_sign(cmd->command[i]))
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
	return (return_unset_env(len, cmd));
}
