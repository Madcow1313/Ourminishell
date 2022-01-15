/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_adjusting_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:08:20 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/16 01:08:21 by wabathur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../logic/logic.h"

/*a bit clunky, but works, i believe*/
char	*delete_a_char(char *string)
{
	char	*new_string;
	char	*temp;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	new_string = malloc(sizeof(string));
	if (!new_string)
		return (NULL);
	temp = string;
	while (string[i] && temp[i])
	{
		while ((string[i] != '\'' && string[i] != '\"') && string[i])
			new_string[j++] = string[i++];
		c = string[i];
		i++;
		while (string[i] != c && string[i])
			new_string[j++] = string[i++];
	}
	new_string[j] = '\0';
	return (new_string);
}

int	delete_quotes(t_list_commands *list)
{
	int		i;

	i = 0;
	while (list->command[i] && i < list->number)
	{
		if (list->type[i] == BUILT_IN || list->type[i] == WORD
			|| list->type[i] == ENVIRONMENT_VAR)
		{
			if (find_first_qm(list->command[i]) < ft_strlen(list->command[i]))
			{
				list->command[i] = delete_a_char(list->command[i]);
				if (!list->command[i])
					return (0);
			}
		}	
		i++;
	}
	return (1);
}
