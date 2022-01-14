/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:44:17 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:44:17 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

void	manage_out_pipe(t_list_commands *cmd)
{
	if (cmd->pipe_right)
	{
		if (cmd->fd[1] != -1)
			write(cmd->fd[1], "\0", 1); //write to stdout_copy? or STD_OUT??
		else
		{
			close(STD_OUT);
			dup2(cmd->fd[1], STD_OUT);
		}
	}
	else if (cmd->pipe_left)
	{
		close(STD_OUT);
		dup2(cmd->stdout_copy, STD_OUT);
	}
}

void	manage_in_pipe(t_list_commands *cmd)
{
	if (cmd->pipe_right)
	{
		close(STD_IN);
		dup2(cmd->fd[0], STD_IN);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
	}
	else if (cmd->pipe_left)
	{
		close(STD_IN);
		dup2(cmd->stdin_copy, STD_IN);
	}
}
