/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:03:26 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/16 01:22:45 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

static void	find_duplicates(char **new_env, int j, int k, int i)
{
	char	*cmp;
	char	*cmp_2;
	int		l;

	l = 0;
	cmp = ft_substr(new_env[j], 0, k);
	while (new_env[i][l] && new_env[i][l] != '=')
		l++;
	cmp_2 = ft_substr(new_env[i], 0, l);
	if (!ft_strcmp(cmp, cmp_2))
	{
		if (new_env[j][k + 1] && new_env[j][k + 1] != '\0')
			new_env[i] = NULL;
		else
			new_env[j] = NULL;
	}
	free(cmp_2);
	free(cmp);
}

void	check_duplicates(char **new_env, int new_len)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i <= new_len)
	{
		if (new_env[i])
		{
			j = i + 1;
			while (j <= new_len)
			{
				k = 0;
				if (new_env[j])
				{
					while (new_env[j][k] && new_env[j][k] != '=')
						k++;
					if (new_env[i])
						find_duplicates(new_env, j, k, i);
				}
				j++;
			}
		}
	}
}

int	check_only_space(char *s)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (s[++i])
	{
		if (s[i] != ' ')
			count = 1;
	}
	if (count == 1)
		return (1);
	return (0);
}

int	check_first_symbol(char c)
{
	if (c == '=' || (c >= 33 && c <= 64) || (c >= 91 && c <= 96)
		|| (c >= 123 && c <= 126))
		return (0);
	return (1);
}

int	wrong_symbols(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '`' || str[i] == '\\' || str[i] == '(' || str[i] == ')'
			|| str[i] == '&' || str[i] == '|')
			return (0);
		i++;
	}
	return (1);
}
