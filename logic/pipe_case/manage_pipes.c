/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:44:17 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/16 02:21:25 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

void	manage_out_pipe(t_list_commands *cmd)
{
	if (cmd->pipe_right)
	{
		close(cmd->stdout_copy);
		dup2(cmd->fd[1], cmd->stdout_copy);
	}
	else if (cmd->pipe_left)
	{
		close(cmd->stdout_copy);
		dup2(cmd->stdout_copy, STDOUT_FILENO);
	}
}

void	manage_in_pipe(t_list_commands *cmd)
{
	if (cmd->pipe_right != -1)
	{
		close(cmd->stdin_copy);
		dup2(cmd->fd[0], cmd->stdin_copy);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
	}
	else if (cmd->pipe_left != -1)
	{
		close(cmd->stdin_copy);
		dup2(cmd->fd[0], cmd->stdin_copy);
	}
}
