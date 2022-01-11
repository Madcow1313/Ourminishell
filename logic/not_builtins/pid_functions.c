/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmilan <dmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:15:32 by dmilan            #+#    #+#             */
/*   Updated: 2021/04/16 16:32:47 by dmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

bool	is_child(pid_t pid)
{
	if (pid == 0)
		return (true);
	return (false);
}

bool	is_parent(pid_t pid)
{
	if (pid > 0)
		return (true);
	return (false);
}
