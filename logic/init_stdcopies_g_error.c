/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stdcopies_g_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:45:49 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 22:50:33 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

void	init_stdcopies_g_error(t_list_commands *cmd, t_command *p)
{
	cmd->p = p;
	cmd->stdin_copy = dup(STD_IN);
	cmd->stdout_copy = dup(STD_OUT);
	g_error_code = 0;
}
