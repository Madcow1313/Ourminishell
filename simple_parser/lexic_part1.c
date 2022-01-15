/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic_part1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:08:54 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/16 01:08:56 by wabathur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*simply fill first struct*/
t_command	*get_full_command(const char *string, t_command *command)
{
	command->len = ft_strlen(string);
	command->word = string;
	return (command);
}

/*counter for single commas*/
size_t	count_single_qm(t_command *command, size_t start, size_t end)
{
	size_t	i;
	size_t	counter;

	i = start;
	counter = 0;
	while (i < end)
	{
		if (command->word[i] == '\'')
			counter++;
		i++;
	}
	return (counter);
}

/*counter for double commas*/
size_t	count_double_qm(t_command *command, size_t start, size_t end)
{
	size_t	i;
	size_t	counter;

	i = start;
	counter = 0;
	while (i < end)
	{
		if (command->word[i] == '\"')
			counter++;
		i++;
	}
	return (counter);
}

/* add ft_strchr and make return int if found*/
size_t	find_first_qm(const char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\'' && string[i] != '\"' && string[i] != '\0')
		i++;
	return (i);
}
