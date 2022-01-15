/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parse_part1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:10:17 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/16 01:10:33 by wabathur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../simple_parser/parser.h"
#include "../logic/logic.h"

void	set_list_for_qm(t_list_commands *list)
{
	list->type[list->number] = DOUBLE_QM;
	list->number += 1;
	list->command[list->number] = NULL;
}

int	proc_quotes(t_list_commands *list)
{
	char	*temp;

	if (list->type[list->number - 1] == DOUBLE_QM)
	{
		while (ft_strchr_for_dq(list->command[list->number - 1], '$')
			>= 0)
		{
			if (ft_strchr_parser(list->command[list->number - 1], '$')
				== (int)ft_strlen(list->command[list->number - 1]) - 1)
			{
				temp = list->command[list->number];
				list->command[list->number] = ft_strdup("");
				if (!list->command[list->number])
					return (0);
				set_list_for_qm(list);
				break ;
			}
			temp = list->command[list->number - 1];
			list->command[list->number - 1]
				= get_prefix_for_env(
					list->env_vars, list->command[list->number - 1]);
			free (temp);
		}
	}
	return (1);
}

int	proc_envp(t_list_commands *list)
{
	char	*temp;

	if (list->command[list->number - 1][0] != '\''
	&& list->command[list->number - 1][0] != '\"'
	&& ft_strlen(list->command[list->number - 1]) > 1)
	{
		temp = list->command[list->number - 1];
		list->command[list->number - 1]
			= get_env_var_value(
				list->env_vars, list->command[list->number - 1] + 1);
		if (!list->command[list->number - 1])
			return (0);
		free (temp);
	}	
	return (1);
}

int	new_alloc_for_f_env(t_list_commands *list, t_command *command)
{
	int		j;
	int		counter;

	counter = 0;
	j = 0;
	while (list->command[0][j])
	{
		if (list->command[0][j] == ' ')
			counter++;
		j++;
	}
	list->command
		= malloc(sizeof(char *) * (command->len + 1)
			+ sizeof(char *) * (counter * 2 + 1));
	list->type
		= malloc(sizeof(int *) * (command->len + 1)
			+ sizeof(int *) * (counter * 2 + 1));
	if (!list->command || !list->type)
		return (0);
	return (1);
}

int	proc_first_env(t_list_commands *list, char **split_string)
{
	int	j;

	j = 0;
	while (split_string[j])
	{
		list->command[list->number] = ft_strdup(split_string[j]);
		if (!list->command[list->number])
			return (0);
		list->type[list->number] = BUILT_IN;
		list->number += 1;
		list->command[list->number] = malloc(1);
		if (!list->command[list->number])
			return (0);
		list->command[list->number][0] = '\0';
		list->type[list->number] = SEP_SPACE;
		list->number += 1;
		list->command[list->number] = NULL;
		j++;
	}
	return (1);
}
