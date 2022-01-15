/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_with_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:43:50 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/15 20:26:55 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

//not sure if i need redir func

/* static void	open_redirections(t_list_commands *cmd)
{
	if (cmd->fd[0] != -1)
	{
		close(STD_IN);
		dup2(cmd->fd[0], STD_IN);
	}
	if (cmd->fd[1] != -1)
	{
		close(STD_OUT);
		dup2(cmd->fd[1], STD_OUT);
	}
}

static void	close_redirections(t_list_commands *cmd)
{
	if (cmd->fd[0] != -1 || cmd->fd[1] != -1)
	{
		if (cmd->fd[1] != -1 && cmd->pipe_right)
			;
		else
		{
			dup2(cmd->stdout_copy, STD_OUT);
			dup2(cmd->stdin_copy, STD_IN);
		}
	}
} */

void	cmd_with_pipes(t_list_commands *cmd)
{
	t_opendir	o_dir;

	ft_putstr_fd("Hello\n", 1);
	if (pipe(cmd->fd) == -1)
	{
		g_error_code = errno;
		ft_putstr_fd("Pipe failed, initializing undefined behavior", STD_ERROR);
	}
	//open_redirections(cmd);
	manage_out_pipe(cmd);
	if (our_builtin(cmd->command[0]))
		single_command(cmd);
	else
		exec(cmd, &o_dir);
	manage_in_pipe(cmd);
	//close_redirections(cmd);
}
