/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_semicol.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:45:18 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:45:18 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

int	check_pipe_semicol(t_list_commands *cmd)
{
	if (!ft_strcmp(cmd->command[0], ";"))
	{
		g_error_code = 2;
		ft_putstr_fd("bash: syntax error near unexpected token ';'\n", 2);
		return (0);
	}
	else if (!ft_strcmp(cmd->command[0], "|"))
	{
		g_error_code = 2;
		ft_putstr_fd("bash: syntax error near unexpected token '|'\n", 2);
		return (0);
	}
	return (1);
}
