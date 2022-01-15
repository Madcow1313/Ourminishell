/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:08:32 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/16 01:59:39 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	prepare_list(t_list_commands *list, t_command *command)
{
	list->command = malloc(sizeof(char *) * (command->len + 1));
	list->type = malloc(sizeof(int *) * (command->len + 1));
	list->fd[0] = 0;
	list->fd[1] = 1;
	if (!list->command || !list->type)
	{
		if (list->command)
			free (list->command);
		if (list->type)
			free (list->type);
		return (-1);
	}
	list->redirect = 0;
	list->pipe_right = 0;
	list->pipe_left = 0;
	list->number = 0;
	return (0);
}
