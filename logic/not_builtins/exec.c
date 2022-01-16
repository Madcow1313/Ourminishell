/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:40:15 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/16 04:07:39 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

static void	call_exec(char *file_path, t_list_commands *cmd)
{
	if (execve(file_path, cmd->command, cmd->env_vars) == -1)
	{
		g_error_code = errno;
		exec_error(cmd);
		return ;
	}
	g_error_code = 0;
}

char	*check_binary(t_list_commands *cmd)
{
	char	*file_path;

	if ((cmd->command[0][0] == '.' && cmd->command[0][1] == '/')
		|| cmd->command[0][0] == '/')
		file_path = ft_strdup(cmd->command[0]);
	else if (cmd->command[0][0] == '.'
		&& cmd->command[0][1] == '.'
		&& cmd->command[0][2] == '/')
		file_path = ft_strdup(cmd->command[0]);
	else
		file_path = NULL;
	return (file_path);
}

char	*keep_searching_path(char *file_path, t_list_commands *cmd)
{
	if (is_command_executable(cmd))
		file_path = ft_strdup(cmd->command[0]);
	else
		file_path = NULL;
	return (file_path);
}

void	exec(t_list_commands *cmd, t_opendir *open_dir)
{
	pid_t	pid;
	char	*file_path;

	file_path = check_binary(cmd);
	if (!file_path)
		file_path = keep_searching_path(file_path, cmd);
	if (!file_path)
		file_path = get_binary_from_path(cmd, open_dir);
	if (file_path)
	{
		pid = fork();
		if (pid == 0)
		{
			call_exec(file_path, cmd);
			process_exit(0);
		}
		else if (pid > 0)
			wait(&pid);
		else
			ft_putstr_fd("Can't execute command, fork failed\n", STD_ERROR);
	}
	else
		puterror_exec("bash: ", cmd->command[0], ": command not found", 127);
	if (file_path)
		free(file_path);
}
