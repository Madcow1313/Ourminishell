/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stdcopies_g_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:45:49 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/14 21:48:14 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

void	init_stdcopies_g_error(t_list_commands *cmd, t_command *p)
{
	cmd->p = p;
	//cmd->stdin_copy = dup(cmd->fd[0]);
	//cmd->stdout_copy = dup(cmd->fd[1]);
	g_error_code = 0;
}
