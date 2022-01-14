/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:40:03 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 17:40:04 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

bool	is_numeric(char *str)
{
	if (!str)
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

void	process_exit(char **args)
{
	ft_putstr_fd("exit\n", STD_ERROR);
	if (!*args || !args)
		exit(g_error_code);
	if (count_env_len(args) > 1)
	{
		ft_putstr_fd("exit: too many arguments\n", STD_ERROR);
		g_error_code = 1;
		return ;
	}
	if (*args && !is_numeric(*args))
	{
		ft_putstr_fd("exit: ", STD_ERROR);
		ft_putstr_fd(*args, STD_ERROR);
		ft_putstr_fd(": numeric argument required\n", STD_ERROR);
		g_error_code = 1;
		exit(225);
	}
	if (*args && is_numeric(*args))
		exit(ft_atoi(*args));
}
