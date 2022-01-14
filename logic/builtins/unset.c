/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:59:48 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:17:06 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

static void	parts_to_compare_unset(char **old_env, char **set)
{
	char	*cmp;
	char	*tmp_set;
	int		i;

	i = 0;
	tmp_set = *set;
	if (!*set || !*old_env || !set || !old_env)
		return ;
	while ((*old_env)[i] && (*old_env)[i] != '=')
		i++;
	cmp = ft_substr(*old_env, 0, i);
	if (!ft_strncmp(tmp_set, cmp, ft_strlen(cmp)))
	{
		if (*old_env && old_env)
			free(*old_env);
		*old_env = NULL;
	}
	free(cmp);
	return ;
}

static char	**return_unset_arr(char **old_env, int old_len)
{
	char	**unset;
	int		len_after_unset;

	len_after_unset = ft_len_after(old_env, old_len);
	unset = fill_unset(old_env, old_len, len_after_unset);
	if (!unset)
		return (old_env);
	return (unset);
}

static char	**unset_env(char **old_env, char **set, int len, int old_len)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	while (old_env[++i] && i <= old_len)
	{
		j = -1;
		while (++j <= len)
		{
			if (set[j])
			{
				k = 0;
				if (old_env[i])
					while (old_env[i][k] && old_env[i][k] != '=')
						k++;
				parts_to_compare_unset(&old_env[i], &set[j]);
			}
		}
	}
	return (return_unset_arr(old_env, old_len));
}

static char	**deleting_new_env_var(t_list_commands *cmd)
{
	char	**new_env;
	int		unset_len;
	int		old_len;

	new_env = check_valid_unset(cmd);
	if (new_env == NULL)
		return (cmd->env_vars);
	unset_len = count_env_len(new_env);
	old_len = count_env_len(cmd->env_vars);
	cmd->env_vars = unset_env(cmd->env_vars, new_env, unset_len, old_len);
	free(new_env);
	return (cmd->env_vars);
}

void	process_unset(t_list_commands *cmd)
{
	g_error_code = 0;
	if (cmd->command[1])
		cmd->env_vars = deleting_new_env_var(cmd);
	return ;
}
