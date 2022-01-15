/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_descriptors3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:13:22 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/16 01:16:48 by wabathur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../logic/logic.h"

int	procedure_first_red(t_list_commands *list)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < list->number - 1 && list->command[i])
	{
		temp = list->command[i];
		if (i == 0)
			list->command[i] = ft_strdup("echo");
		else if (i == 1)
			list->command[i] = ft_strdup("-n");
		else
			list->command[i] = ft_strdup(" ");
		if (!list->command[i])
			return (0);
		list->type[i] = BUILT_IN;
		free (temp);
		i++;
	}
	return (1);
}

int	procedure_repoints_part_2(t_list_commands *list, int i, char *temp)
{
	while (i < list->number)
	{
		if (!list->command[i + 2])
		{
			temp = list->command[i];
			list->command[i]
				= ft_strdup(repoint(list->command[i + 1],
						NULL, list->type, i));
			free (temp);
			break ;
		}
		else
		{
			temp = list->command[i];
			list->command[i]
				= ft_strdup(repoint(list->command[i + 1],
						list->command[i + 2], list->type, i));
			i++;
			free (temp);
		}
	}
	return (1);
}

int	procedure_repoints(t_list_commands *list, int i)
{
	char	*temp;

	if (list->command[i])
	{
		if (list->command[i + 1])
		{
			temp = list->command[i];
			list->command[i]
				= ft_strdup(repoint(list->command[i + 1],
						list->command[i + 2], list->type, i));
			if (!list->command[i])
				return (0);
			free (temp);
		}
		else
			return (-1);
	}
	if (list->command[i + 1])
		procedure_repoints_part_2(list, i + 1, temp);
	return (1);
}

int	throw_fd_error(t_list_commands *list, int i)
{
	write(1, "bash :", 7);
	perror(list->command[i + 1]);
	return (-1);
}

int	rid_of_redirect_right(t_list_commands *list)
{
	int	i;

	i = 0;
	while ((list->type[i] != REDIRECT_RIGHT && list->type[i] != REDIRECT_LEFT
			&& list->type[i] != REDIRECT_AND_APPEND
			&& list->type[i] != HERE_DOC)
		&& list->command[i] && i < list->number)
		i++;
	if (list->type[i] == REDIRECT_RIGHT || list->type[i] == REDIRECT_AND_APPEND)
		list->fd[1]
			= get_fd_right_redirects(list, list->command[i + 1], list->type[i]);
	else if (list->type[i] == REDIRECT_LEFT)
		list->fd[0]
			= get_fd_left_redirects(list, list->command[i + 1], list->type[i]);
	else if (list->type[i] == HERE_DOC)
		list->fd[0] = get_here_doc(list->command[i + 1], list);
	if (list->fd[0] == -1 || list->fd[1] == -1)
		return (throw_fd_error(list, i));
	if (list->number <= 3 && list->type[0] >= REDIRECT_RIGHT
		&& list->type[0] <= REDIRECT_AND_APPEND)
		procedure_first_red(list);
	else
		procedure_repoints(list, i);
	return (0);
}
