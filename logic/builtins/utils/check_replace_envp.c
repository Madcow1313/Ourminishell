/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_replace_envp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:18:48 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/16 01:26:28 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

static char	**return_filled(char **old, char **new, int len_2, char **filled)
{
	int		i;
	int		j;

	i = -1;
	while (old[++i])
		filled[i] = old[i];
	free(old);
	j = -1;
	while (++j <= len_2)
	{
		if (new[j])
		{
			filled[i] = ft_strdup(new[j]);
			i++;
		}
	}
	filled[i] = NULL;
	return (filled);
}

static char	**join_ostatok(char **old, char **new, int len, int len_2)
{
	int		old_len;
	char	**filled_env;

	if (!len || new == NULL)
		return (old);
	old_len = count_env_len(old);
	filled_env = malloc(sizeof(char *) * (len + old_len + 1));
	if (!filled_env)
	{
		malloc_error(filled_env);
		return (old);
	}
	return (return_filled(old, new, len_2, filled_env));
}

static void	do_replace(char **old, char **new)
{
	if (*old)
		free(*old);
	*old = ft_strdup(*new);
	*new = NULL;
	return ;
}

void	parts_to_compare(char **old_env, char **new_env, int k)
{
	char	*cmp;
	char	*cmp_2;
	int		i;

	i = 0;
	if (!*new_env || !*old_env)
		return ;
	cmp = ft_substr(*new_env, 0, k);
	while ((*old_env)[i] && (*old_env)[i] != '=')
		i++;
	cmp_2 = ft_substr(*old_env, 0, i);
	if (!ft_strcmp(cmp, cmp_2))
	{
		if ((*new_env)[k] == '\0' && *new_env)
			*new_env = NULL;
		else
			do_replace(old_env, new_env);
	}
	free(cmp_2);
	free(cmp);
	return ;
}

char	**check_replace_env(char **old_env, char **new_env, int len)
{
	int		i;
	int		j;
	int		k;
	char	**result;
	int		len_after_check_replace;

	i = -1;
	while (old_env[++i])
	{
		j = -1;
		while (++j <= len)
		{
			if (new_env[j])
			{
				k = 0;
				while (new_env[j][k] && new_env[j][k] != '=')
					k++;
				if (new_env[j])
					parts_to_compare(&old_env[i], &new_env[j], k);
			}
		}
	}
	len_after_check_replace = ft_len_after(new_env, len);
	result = join_ostatok(old_env, new_env, len_after_check_replace, len);
	return (result);
}
