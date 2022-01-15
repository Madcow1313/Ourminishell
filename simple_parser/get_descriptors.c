/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_descriptors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:12:57 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/16 01:17:06 by wabathur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../logic/logic.h"

/*i have no idea what should i do
still in progress*/
int	get_fd_left_redirects(t_list_commands *list, char *path, int type)
{
	int	fd_to_apply;

	list->old_stdin = dup(STDIN_FILENO);
	list->old_stdout = dup(STDOUT_FILENO);
	fd_to_apply = 0;
	if (type == REDIRECT_LEFT)
	{
		fd_to_apply = open(path, O_RDONLY);
		if (fd_to_apply < 0)
			return (-1);
	}
	list->fd[0] = fd_to_apply;
	return (list->fd[0]);
}

int	get_fd_right_redirects(t_list_commands *list, char *path, int type)
{
	int	fd_to_apply;

	list->old_stdin = dup(STDIN_FILENO);
	list->old_stdout = dup(STDOUT_FILENO);
	fd_to_apply = 1;
	if (type == REDIRECT_RIGHT)
		fd_to_apply = open(path, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	else if (type == REDIRECT_AND_APPEND)
		fd_to_apply = open(path, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
	if (fd_to_apply < 0)
		return (-1);
	list->fd[1] = fd_to_apply;
	return (list->fd[1]);
}

void	set_default_fd(void)
{
	int	ttyfd;

	ttyfd = open("/dev/tty", O_RDWR);
	dup2(ttyfd, STDOUT_FILENO);
	dup2(ttyfd, STDIN_FILENO);
	close(ttyfd);
}

int	get_redirect_type(t_list_commands *list)
{
	int	i;

	i = 0;
	while (list->command[i] && i < list->number)
	{
		if (list->type[i] == REDIRECT_RIGHT
			|| list->type[i] == REDIRECT_AND_APPEND
			|| list->type[i] == REDIRECT_LEFT || list->type[i] == HERE_DOC)
		{
			if (!list->command[i + 1])
				return (-1);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*repoint(char *string1, char *string2, int *type, int i)
{
	string1 = string2;
	type[i] = type[i + 2];
	return (string1);
}
