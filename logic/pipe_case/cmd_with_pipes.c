/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_with_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 22:43:59 by jmaryett          #+#    #+#             */
/*   Updated: 2022/01/15 23:48:40 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

void	open_pipes(t_list_commands *cmd)
{
	if (cmd->pipe_right != -1)
	{
		if (pipe(cmd->fd) == -1)
		{
			g_error_code = errno;
			ft_putstr_fd("Pipe, failed, initializing undefined behavior\n", STD_ERROR);
		}
	}
}

void	check_right_pipe(t_list_commands *cmd)
{
	if (cmd->pipe_right != -1)
	{
		open_pipes(cmd);
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
	}
}

void	check_left_pipe(t_list_commands *cmd)
{
	if (cmd->pipe_right != -1)
	{
		dup2(cmd->fd[0], STDIN_FILENO);
		close(cmd->fd[0]);
		dup2(STD_OUT, STDOUT_FILENO);
	}
	if (cmd->pipe_right == -1)
		dup2(STD_IN, STDIN_FILENO);
}

void	cmd_with_pipes(t_list_commands *cmd, t_opendir *o_dir)
{
	check_right_pipe(cmd);
	if (our_builtin(cmd->command[0]))
		single_command(cmd, o_dir);
	else
		exec(cmd, o_dir);
	check_left_pipe(cmd);
}
