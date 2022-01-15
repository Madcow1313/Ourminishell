/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stdcopies_g_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:45:49 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/16 02:22:32 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

void	init_stdcopies_g_error(t_list_commands *cmd, t_command *p)
{
	cmd->p = p;
	g_error_code = 0;
}
