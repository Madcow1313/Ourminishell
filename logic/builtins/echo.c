/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:37:58 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/15 19:19:01 by jmaryett         ###   ########.fr       */
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
			write(cmd->stdout_redir, &(cmd->command[i][j]), 1);
			//write(cmd->fd[1], &(cmd->command[i][j]), 1);
			j++;
		}
		if (cmd->command[i + 1])
			write(cmd->stdout_redir, " ", 1);//write(cmd->fd[1], " ", 1);
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
			write(cmd->stdout_redir, &(cmd->command[i][j]), 1);//write(cmd->fd[1], &(cmd->command[i][j]), 1);
			j++;
		}
		if (cmd->command[i + 1])
			write(cmd->stdout_redir, " ", 1);
		i++;
	}
	write (cmd->stdout_redir, "\n", 1);
	return ;
}

int	check_valid_fd(t_list_commands *cmd)
{
	struct stat	buf;
	
	if (cmd->stdout_redir == -1)
		return (g_error_code);
	else
	{
		if (fstat(cmd->stdout_redir, &buf) == 0 && S_ISDIR(buf.st_mode))
		{
			g_error_code = 1;
			return (g_error_code);
		}
	}
	return (0);
}

void	process_echo(t_list_commands *cmd)
{
	//printf("%s\n", "All good");
	g_error_code = check_valid_fd(cmd);
	if (g_error_code == 1)
		return ;
	if (cmd->command[1] != NULL)
	{
		if (!ft_strcmp(cmd->command[1], "-n"))
			echo_without_newline(cmd);
		else
			echo_with_newline(cmd);
	}
	else
		write(cmd->stdout_redir, "\n", 1);
	return ;
}
