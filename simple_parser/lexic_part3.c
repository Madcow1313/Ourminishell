/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic_part3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:11:15 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/16 01:11:16 by wabathur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../logic/logic.h"

/*can't handle slash '\' */
int	handle_quotes(
		t_list_commands *list, t_command *command, int character, size_t *i)
{
	size_t	count;
	size_t	start;
	char	quoute;

	count = 0;
	*i += 1;
	start = *i;
	if (character == SINGLE_QM)
		quoute = '\'';
	else
		quoute = '\"';
	while (command->word[*i] != quoute && command->word[*i] != '\0')
	{
		*i += 1;
		count++;
	}
	list->command[list->number] = malloc(count + 1);
	ft_strlcpy(list->command[list->number], command->word + start, count + 1);
	list->number += 1;
	list->command[list->number] = NULL;
	list->type[list->number] = BUILT_IN;
	return (0);
}

int	handle_redirects(t_list_commands *list, int character, size_t *i)
{
	char	*temp;

	list->command[list->number] = malloc(4);
	temp = list->command[list->number];
	if (!list->command[list->number])
		return (0);
	if (character == REDIRECT_RIGHT)
		list->command[list->number] = ft_strdup(">");
	else if (character == REDIRECT_LEFT)
		list->command[list->number] = ft_strdup("<");
	else if (character == REDIRECT_AND_APPEND)
		list->command[list->number] = ft_strdup(">>");
	else if (character == HERE_DOC)
		list->command[list->number] = ft_strdup("<<");
	*i += ft_strlen(list->command[list->number]);
	list->number += 1;
	list->command[list->number] = NULL;
	free (temp);
	return (1);
}
