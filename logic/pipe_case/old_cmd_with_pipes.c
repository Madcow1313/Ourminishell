/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_cmd_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:43:50 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/16 02:21:40 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

void	cmd_with_pipes(t_list_commands *cmd)
{
	t_opendir	o_dir;

	ft_putstr_fd("Hello\n", 1);
	if (pipe(cmd->fd) == -1)
	{
		g_error_code = errno;
		ft_putstr_fd("Pipe failed, initializing undefined behavior", STD_ERROR);
	}
	manage_out_pipe(cmd);
	if (our_builtin(cmd->command[0]))
		single_command(cmd);
	else
		exec(cmd, &o_dir);
	manage_in_pipe(cmd);
}
