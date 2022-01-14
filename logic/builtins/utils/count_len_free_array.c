/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_len_free_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:44:51 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:30:57 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

//counts double array's len(not str len)
int	count_env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	ft_len_after(char **env, int old_len)
{
	int	i;
	int	len_after;

	i = -1;
	len_after = 0;
	while (++i <= old_len)
		if (env[i])
			len_after++;
	return (len_after);
}

char	**free_array(char **env)
{
	int	i;
	int	env_len;

	i = 0;
	if (!env)
		return (NULL);
	env_len = count_env_len(env);
	while (i <= env_len)
	{
		if (env[i])
			free (env[i]);
		i++;
	}
	free(env);
	env = NULL;
	return (env);
}
