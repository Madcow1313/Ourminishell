/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:42:11 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/14 20:16:33 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

void	exec_error(t_list_commands *cmd/* , char *file_path */)
{
	//if (file_path)
		//free(file_path);
	ft_putstr_fd("Error: ", STD_ERROR);
	ft_putstr_fd(cmd->command[0], STD_ERROR);
	ft_putstr_fd(" ", STD_ERROR);
	errors();
}

int	puterror_exec(char *s1, char *s2, char *s3, int code)
{
	g_error_code = code;
	write(2, s1, ft_strlen(s1));
	write(2, s2, ft_strlen(s2));
	write(2, s3, ft_strlen(s3));
	write(2, "\n", 1);
	return (code);
}
