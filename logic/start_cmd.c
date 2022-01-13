/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:48:41 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 23:36:57 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

static void	free_cmd(t_list_commands *cmd)
{
	size_t	i;

	i = 0;
	// printf("Start array\n");
	// while (1) {
	// 	i++;
	// 	ft_putstr_fd(cmd->command[i], 1);
	// }
	// printf("End array\n");
	// free_array(cmd->command);
	if (cmd->command)
	{
		while (cmd->command[i]) {
			free(cmd->command[i]);
			i++;
		}
	}
	free(cmd->command);
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
	printf("%d\n", cmd->pipe_right);
	print_commands_and_words(cmd);
	if (cmd->command[0] == NULL || !cmd->command)
		return ;
	if (!check_pipe_semicol(cmd))
		return ;
	if (!count_pipes(cmd) || (cmd->pipe_right == -1
			&& cmd->pipe_left == -1))
		single_command(cmd);
	else
		cmd_with_pipes(cmd);	
	return ;
}

void	start_cmd(t_list_commands *cmd)
{	
	//cmd->p = p;
	ft_s_h();
	check_start_cmd(cmd);
	free_cmd(cmd);
	return ;
}
