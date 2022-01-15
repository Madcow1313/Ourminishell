/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:08:32 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/16 01:11:00 by wabathur         ###   ########.fr       */
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
	list->pipe_right = -1;
	list->pipe_left = -1;
	list->number = 0;
	return (0);
}
