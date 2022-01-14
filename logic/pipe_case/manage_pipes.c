/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:44:17 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/14 21:52:32 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

void	manage_out_pipe(t_list_commands *cmd)
{
	if (cmd->pipe_right != -1)
	{
		if (cmd->fd[1] != -1)
			write(cmd->fd[1], "\0", 1); //write to stdout_copy? or STD_OUT??
		else
		{
			close(STD_OUT);
			dup2(cmd->fd[1], STD_OUT);
		}
	}
	else if (cmd->pipe_left != -1)
	{
		close(STD_OUT);
		dup2(cmd->stdout_copy, STD_OUT);
	}
/* 	if (cmd->pipe_right)
	{
		if (cmd->fd[1] != -1)
		{
			close(cmd->fd[1]);
			dup2(cmd->stdin_copy, cmd->fd[1]);
		}
		else
			return ;
	}
	else if (cmd->pipe_left) */
}

void	manage_in_pipe(t_list_commands *cmd)
{
	if (cmd->pipe_right != -1)
	{
		close(STD_IN);
		dup2(cmd->fd[0], STD_IN);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
	}
	else if (cmd->pipe_left != -1)
	{
		close(STD_IN);
		dup2(cmd->stdin_copy, STD_IN);
	}
}
