/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:44:22 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/15 16:47:12 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

int	our_builtin(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (true);
	else if (ft_strcmp(command, "echo") == 0)
		return (true);
	else if (ft_strcmp(command, "env") == 0)
		return (true);
	else if (ft_strcmp(command, "exit") == 0)
		return (true);
	else if (ft_strcmp(command, "export") == 0)
		return (true);
	else if (ft_strcmp(command, "pwd") == 0)
		return (true);
	else if (ft_strcmp(command, "unset") == 0)
		return (true);
	return (false);
}
