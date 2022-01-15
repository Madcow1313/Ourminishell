/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_adjusting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:08:36 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/16 01:08:37 by wabathur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../logic/logic.h"

int	count_size_2(int *i, int size, char *string)
{
	while (string[*i] && (ft_isalnum(string[*i]) || string[*i] == '_'))
	{
		size++;
		*i += 1;
	}
	return (size);
}

char	*count_size(char *string, char **env_vars, char *new_string, char *temp)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	size = count_size_2(&i, size, string);
	if (size != 0)
	{
		temp += i;
		i = 0;
		while (env_vars[i])
		{
			if (!ft_strncmp(env_vars[i], string, size))
			{
				if (env_vars[i][size] == '=')
				{
					string = env_vars[i] + size + 1;
					new_string = ft_strjoin(string, temp);
					return (new_string);
				}
			}
			i++;
		}
	}
	return (NULL);
}

char	*get_env_var_value(char **env_vars, char *string)
{
	char	*temp;
	char	*new_string;
	int		i;

	i = 0;
	temp = string;
	new_string = NULL;
	if (string[i] == '\'' || string[i] == '\"')
		return (string);
	if (string[i] == '?')
	{
		temp = ft_strdup(ft_itoa(g_error_code));
		return (temp);
	}
	new_string = count_size(string, env_vars, new_string, temp);
	if (!new_string)
	{
		string[0] = '\0';
		new_string = ft_strjoin(string, temp);
	}
	return (new_string);
}

char	*get_prefix_for_env(char **env_vars, char *string)
{
	char	*temp;
	char	*temp2;
	char	*new_string;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (string[i])
	{
		if (string[i] == '$' && string[i + 1] != ' ')
			break ;
		i++;
		size++;
	}
	temp = malloc(size + 1);
	if (!temp)
		return (string);
	i = 0;
	ft_strlcpy(temp, string, size + 1);
	temp2 = get_env_var_value(env_vars, (string + size + 1));
	new_string = ft_strjoin(temp, temp2);
	free (temp);
	free (temp2);
	return (new_string);
}
