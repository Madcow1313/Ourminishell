/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_descriptors_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:12:00 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/16 01:16:35 by wabathur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../logic/logic.h"

void	here_doc_staff(int fd, char *line, char *new_line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	free (new_line);
}

int	get_here_doc(char *end, t_list_commands *list)
{
	char	*line;
	char	*temp;
	char	*new_line;
	int		fd;

	fd = open(".here_doc_minishell", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	while (1)
	{
		line = readline("heredoc>");
		if (!line)
			break ;
		temp = line;
		new_line = get_prefix_for_env(list->env_vars, line);
		line = ft_strdup(new_line);
		free (temp);
		if (!ft_strncmp(line, end, ft_strlen(line)) && ft_strlen(line) > 0)
		{
			free (new_line);
			free (line);
			break ;
		}
		here_doc_staff(fd, line, new_line);
	}
	get_fd_left_redirects(list, ".here_doc_minishell", REDIRECT_LEFT);
	return (list->fd[0]);
}
