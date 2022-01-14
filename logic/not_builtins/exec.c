/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:40:15 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/14 19:53:21 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

static void	call_exec(char *file_path, t_list_commands *cmd)
{
	if (execve(file_path, cmd->command, cmd->env_vars) == -1)
	{
		g_error_code = errno;
		exec_error(cmd/* , file_path */);
		return ;
	}
	g_error_code = 0;
}


char	*check_binary(t_list_commands *cmd)
{
	char	*file_path;

	if ((cmd->command[0][0]== '.' && cmd->command[0][1] == '/')
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

void	exec(t_list_commands *cmd, t_opendir *open_dir)
{
	pid_t	pid;
	char	*file_path;

	file_path = check_binary(cmd);
	if (!file_path)
	{
		if (is_command_executable(cmd))
			file_path = ft_strdup(cmd->command[0]);
		else
			file_path = NULL;
	}
	if (!file_path)
		file_path = get_binary_from_path(cmd, open_dir);
	printf("file_path = %s\n", file_path);
	if (file_path)
	{
		pid = fork();
		if (pid == 0)
			call_exec(file_path, cmd);
		else if (pid > 0)
			wait(&pid);
		else
			ft_putstr_fd("Can't execute command, fork failed\n", STD_ERROR);
	}
	else
		puterror_exec("bash: ", cmd->command[0], ": command not found", 127); //command_error(cmd->command[0]);
	if (file_path)
		free(file_path);
}
