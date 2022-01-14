/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:42:11 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:42:11 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

void	exec_error(t_list_commands *cmd, char *file_path)
{
	if (file_path)
		free(file_path);
	ft_putstr_fd("Error: ", STD_ERROR);
	ft_putstr_fd(cmd->command[0], STD_ERROR);
	ft_putstr_fd(" ", STD_ERROR);
	errors();
}
