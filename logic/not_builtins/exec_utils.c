/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:42:21 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/14 18:57:54 by chudapak         ###   ########.fr       */
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

bool	is_file_exists(char *path)
{
	struct stat		stats;

	if (stat(path, &stats) == -1)
		return (false);
	return (true);
}

bool	is_directory(char *path)
{
	struct stat		stats;

	if (stat(path, &stats) == 0 && S_ISDIR(stats.st_mode))
		return (true);
	return (false);
}

bool	has_execute_permission(char *path)
{
	struct stat		stats;

	if (stat(path, &stats) == 0 && stats.st_mode & S_IXUSR)
		return (true);
	return (false);
}

bool	is_command_executable(t_list_commands *cmd)
{
	if (is_directory(cmd->command[0]))
	{
		g_error_code = 126;//puterror_exec(NULL, cmd->command[0], ": is a directory", 126);
		return (false);
	}
	else if (!is_file_exists(cmd->command[0]))
	{
		//puterror_exec(NULL, cmd->command[0],
		//	": No such file or directory", 127);
		g_error_code = 127;
		return (false);
	}
	else if (!has_execute_permission(cmd->command[0]))
	{
		g_error_code = 126; //puterror_exec(NULL, cmd->command[0], ": Permission denied", 126);
		return (false);
	}
	return (true);
}
