/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:37:58 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/16 01:12:38 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

static void	echo_without_newline(t_list_commands *cmd)
{
	int	i;
	int	j;

	i = 2;
	while (cmd->command[i])
	{
		j = 0;
		while (cmd->command[i][j])
		{
			write(STDOUT_FILENO, &(cmd->command[i][j]), 1);
			j++;
		}
		if (cmd->command[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	return ;
}

static void	echo_with_newline(t_list_commands *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->command[i])
	{
		j = 0;
		while (cmd->command[i][j])
		{
			write(STDOUT_FILENO, &(cmd->command[i][j]), 1);
			j++;
		}
		if (cmd->command[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	write (STDOUT_FILENO, "\n", 1);
	return ;
}

void	process_echo(t_list_commands *cmd)
{
	if (cmd->fd[1] == -1)
	{
		ft_putstr_fd("Wrong fd\n", STD_ERROR);
		return ;
	}
	if (cmd->command[1] != NULL)
	{
		if (!ft_strcmp(cmd->command[1], "-n"))
			echo_without_newline(cmd);
		else
			echo_with_newline(cmd);
	}
	else
		write(STDOUT_FILENO, "\n", 1);
}
