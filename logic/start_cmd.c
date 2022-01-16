/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 02:23:22 by jmaryett          #+#    #+#             */
/*   Updated: 2022/01/16 03:25:26 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

void	free_cmd(t_list_commands *cmd)
{
	size_t	i;

	i = -1;
	if (cmd->command)
	{
		while (cmd->command[++i])
			free(cmd->command[i]);
	}
	cmd->command = NULL;
	i = -1;
	if (cmd->type)
		free(cmd->type);
}

int	count_pipes(t_list_commands *cmd)
{
	int	i;
	int	count;

	count = 0;
	i = 1;
	while (cmd->command[i])
	{
		if (cmd->command[i] && !ft_strcmp(cmd->command[i], "|"))
			count++;
		i++;
	}
	if (count > 0)
		return (1);
	else
		return (0);
}

void	check_start_cmd(t_list_commands *cmd)
{	
	t_opendir	open_dir;

	cmd->redirect = 0;
	if (cmd->command[0] == NULL || !cmd->command)
		return ;
	else if (!check_pipe_semicol(cmd))
		return ;
	else if (!cmd->redirect)
		cmd_with_pipes(cmd, &open_dir);
	else if (cmd->redirect)
		single_command(cmd, &open_dir);
	else if (cmd->pipe_right <= 0
		&& cmd->pipe_left <= 0)
		single_command(cmd, &open_dir);
	else
		cmd_with_pipes(cmd, &open_dir);
	return ;
}

void	start_cmd(t_list_commands *cmd)
{
	ft_s_h();
	check_start_cmd(cmd);
	return ;
}
