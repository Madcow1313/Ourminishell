/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:37:58 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/14 20:17:46 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

/* static int	check_redir(t_list_commands *cmd, int nl)
{
	size_t	i;

	i = 0;
	while (i < cmd->p->len)
	{
		if (cmd->type[i] == REDIRECT_RIGHT ||
			cmd->type[i] == REDIRECT_AND_APPEND)
		{
			redirects(cmd, nl);
			return (0);
		}
		i++;
	}
	return (1);
} */

static void	echo_without_newline(t_list_commands *cmd)
{
	int	i;
	int	j;

	i = 2;
	//if (!check_redir(cmd, 0))
		//return ;
	while (cmd->command[i])
	{
		j = 0;
		while (cmd->command[i][j])
		{
			write(cmd->fd[1], &(cmd->command[i][j]), 1);
			j++;
		}
		if (cmd->command[i + 1])
			write(cmd->fd[1], " ", 1);
		i++;
	}
	return ;
}

static void	echo_with_newline(t_list_commands *cmd)
{
	int	i;
	int	j;

	i = 1;
	//if (!check_redir(cmd, STD_OUT)
		//return ;
	while (cmd->command[i])
	{
		j = 0;
		while (cmd->command[i][j])
		{
			write(cmd->fd[1], &(cmd->command[i][j]), 1);
			j++;
		}
		if (cmd->command[i + 1])
			write(cmd->fd[1], " ", 1);
		i++;
	}
	write (cmd->fd[1], "\n", 1);
	return ;
}

void	process_echo(t_list_commands *cmd)
{
	//printf("%s\n", "All good");
	if (cmd->command[1] != NULL)
	{
		if (!ft_strcmp(cmd->command[1], "-n"))
			echo_without_newline(cmd);
		else
			echo_with_newline(cmd);
	}
	else
		write(cmd->fd[1], "\n", 1);
	g_error_code = 0;
	return ;
}
