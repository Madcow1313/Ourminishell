/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:47:14 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/15 23:23:59 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

void	single_command(t_list_commands *cmd, t_opendir *o_dir)
{
	if (!ft_strcmp(cmd->command[0], "echo")
		|| (!ft_strcmp(cmd->command[0], " ") && cmd->fd[1] != -1))
		process_echo(cmd);
	else if (!ft_strcmp(cmd->command[0], "cd"))
		process_cd(cmd);
	else if (!ft_strcmp(cmd->command[0], "pwd"))
		process_pwd(cmd);
	else if (!ft_strcmp(cmd->command[0], "export"))
		process_export(cmd);
	else if (!ft_strcmp(cmd->command[0], "unset"))
		process_unset(cmd);
	else if (!ft_strcmp(cmd->command[0], "env"))
		process_env(cmd);
	else if (!ft_strcmp(cmd->command[0], "exit"))
		process_exit(cmd->command);
	else
		exec(cmd, o_dir);
	return ;
}
