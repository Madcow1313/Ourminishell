/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_old_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:31:23 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:31:59 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

static char	**create_old_pwd(char **new_env, t_list_commands *cmd, int len)
{
	int	i;

	i = -1;
	new_env = malloc(sizeof(char *) *(len + 2));
	if (!new_env)
	{
		malloc_error(new_env);
		return (cmd->env_vars);
	}
	i = -1;
	while (cmd->env_vars[++i])
		new_env[i] = cmd->env_vars[i];
	i++;
	new_env[i] = ft_strdup("OLDPWD=");
	i++;
	new_env[i] = NULL;
	return (new_env);
}

char	**find_old_pwd(t_list_commands *cmd)
{
	int		i;
	char	**new_env;
	int		len;

	i = -1;
	new_env = NULL;
	len = count_env_len(cmd->env_vars);
	while (cmd->env_vars[++i])
	{
		if (!cmpr_oldpwd(cmd, i))
			return (cmd->env_vars);
	}
	new_env = create_old_pwd(new_env, cmd, len);
	free(cmd->env_vars);
	cmd->env_vars = NULL;
	return (new_env);
}
