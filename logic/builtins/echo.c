/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:37:58 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/15 23:41:48 by jmaryett         ###   ########.fr       */
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
			write(STDOUT_FILENO, &(cmd->command[i][j]), 1);
			//write(cmd->fd[1], &(cmd->command[i][j]), 1);
			j++;
		}
		if (cmd->command[i + 1])
			write(STDOUT_FILENO, " ", 1);//write(cmd->fd[1], " ", 1);
		i++;
	}
	printf("cmd = %s\n",  cmd->command[0]);
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
			write(STDOUT_FILENO, &(cmd->command[i][j]), 1);//write(cmd->fd[1], &(cmd->command[i][j]), 1);
			j++;
		}
		if (cmd->command[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	write (STDOUT_FILENO, "\n", 1);
	printf("cmd = %s\n",  cmd->command[0]);
	return ;
}

/* int	check_valid_fd(t_list_commands *cmd)
{
	struct stat	buf;
	
	if (STDOUT_FILENO == -1)
		return (g_error_code);
	else
	{
		if (fstat(STDOUT_FILENO, &buf) == 0 && S_ISDIR(buf.st_mode))
		{
			g_error_code = 1;
			return (g_error_code);
		}
	}
	printf("cmd = %s\n",  cmd->command[0]);
	return (0);
} */

void	process_echo(t_list_commands *cmd)
{
	//printf("%s\n", "All good");
	//g_error_code = check_valid_fd(cmd);
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
	//printf("cmd = %s\n",  cmd->command[0]);
}
