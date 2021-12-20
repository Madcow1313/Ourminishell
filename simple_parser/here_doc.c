#include "parser.h"
/*
void	get_here_doc(char *end, t_list_commands *list)
{
	char	*line;
	int		fd;

	fd = open(".here_doc_minishell", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	while (1)
	{
		line = readline(">");
		if (!line)
			break;
		get_prefix_for_env(list->env_vars, line);
		if (!ft_strncmp(line, end, ft_strlen(line)))
		{
			free (line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}*/
