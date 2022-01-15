/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:42:21 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/16 02:08:06 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

/*compare strings, returns int (0, >0, <0)*/

int	ft_cmprcmd(const char *string1, const char *string2)
{
	size_t				i;
	size_t				len1;
	size_t				len2;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = 0;
	str1 = (const unsigned char *) string1;
	str2 = (const unsigned char *) string2;
	len1 = ft_strlen((const char *)str1);
	len2 = ft_strlen((const char *)str2);
	if (len1 != len2)
		return (-1);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}

int	is_file_exists(char *path)
{
	struct stat		stats;

	if (stat(path, &stats) == -1)
		return (FALSE);
	return (TRUE);
}

int	is_directory(char *path)
{
	struct stat		stats;

	if (stat(path, &stats) == 0 && S_ISDIR(stats.st_mode))
		return (TRUE);
	return (FALSE);
}

int	has_execute_permission(char *path)
{
	struct stat		stats;

	if (stat(path, &stats) == 0 && stats.st_mode & S_IXUSR)
		return (TRUE);
	return (FALSE);
}

int	is_command_executable(t_list_commands *cmd)
{
	if (is_directory(cmd->command[0]))
	{
		g_error_code = 126;
		return (FALSE);
	}
	else if (!is_file_exists(cmd->command[0]))
	{
		g_error_code = 127;
		return (FALSE);
	}
	else if (!has_execute_permission(cmd->command[0]))
	{
		g_error_code = 126;
		return (FALSE);
	}
	return (TRUE);
}
