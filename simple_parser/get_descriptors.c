#include "parser.h"
#include "../logic/logic.h"

int	get_fd_left_redirects(t_list_commands *list, char *path, int type);

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
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		free (new_line);
	}
	close (fd);
	get_fd_left_redirects(list, ".here_doc_minishell", REDIRECT_LEFT);
	return (list->fd[0]);
}

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
		//dup2(fd_to_apply, STDIN_FILENO);
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
	//dup2(fd_to_apply, list->fd[1]);
	list->fd[1] = fd_to_apply;
	return (list->fd[1]);
}

void	set_default_fd(t_list_commands *list)
{
	int	ttyfd;

	ttyfd = open("/dev/tty", O_RDWR);
	dup2(ttyfd, STDOUT_FILENO);
	dup2(ttyfd, STDIN_FILENO);
	close(ttyfd);
	dup2(list->fd[1], list->old_stdout);
	//list->fd[1] = list->fd[1];
}

int	get_redirect_type(t_list_commands *list)
{
	int	i;

	i = 0;
	while (i <= list->number && list->command[i])
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

int	procedure_first_red(t_list_commands *list)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < list->number - 1 && list->command[i])
	{
		temp = list->command[i];
		if (i == 0)
			list->command[i] = ft_strdup("echo");
		else if (i == 1)
			list->command[i] = ft_strdup("-n");
		else
			list->command[i] = ft_strdup(" ");
		if (!list->command[i])
			return (0);
		list->type[i] = BUILT_IN;
		free (temp);
		i++;
	}
	return (1);
}

int	procedure_repoints_part_2(t_list_commands *list, int i, char *temp)
{
	while (i < list->number)
	{
		if (!list->command[i + 2])
		{
			temp = list->command[i];
			list->command[i]
				= ft_strdup(repoint(list->command[i + 1],
						NULL, list->type, i));
			if (!list->command[i])
				return (0);
			free (temp);
			break ;
		}
		else
		{
			temp = list->command[i];
			list->command[i]
				= ft_strdup(repoint(list->command[i + 1],
						list->command[i + 2], list->type, i));
			if (!list->command[i])
				return (0);
			i++;
			free (temp);
		}
	}
	return (1);
}

int	procedure_repoints(t_list_commands *list, int i)
{
	char	*temp;

	//temp = NULL;
	if (list->command[i])
	{
		if (list->command[i + 1])
		{
			temp = list->command[i];
			list->command[i]
				= ft_strdup(repoint(list->command[i + 1],
						list->command[i + 2], list->type, i));
			if (!list->command[i])
				return (0);
			free (temp);
		}
		else
			return (-1);
	}
	if (list->command[i + 1])
		procedure_repoints_part_2(list, i + 1, temp);
	return (1);
}

int	throw_fd_error(t_list_commands *list, int i)
{
	write(1, "bash :", 7);
	perror(list->command[i + 1]);
	return (-1);
}

/*a lot of leaks, should be.
function works next way:
it change arrays
and set list->fd[1] to the last redirected file.
it doesn't close files!!!!*/
int	rid_of_redirect_right(t_list_commands *list)
{
	int	i;

	i = 0;
	while ((list->type[i] != REDIRECT_RIGHT && list->type[i] != REDIRECT_LEFT
			&& list->type[i] != REDIRECT_AND_APPEND
			&& list->type[i] != HERE_DOC)
		&& list->command[i] && i < list->number)
		i++;
	if (list->type[i] == REDIRECT_RIGHT || list->type[i] == REDIRECT_AND_APPEND)
		list->fd[1]
			= get_fd_right_redirects(list, list->command[i + 1], list->type[i]);
	else if (list->type[i] == REDIRECT_LEFT)
		list->fd[0]
			= get_fd_left_redirects(list, list->command[i + 1], list->type[i]);
	else if (list->type[i] == HERE_DOC)
		list->fd[0] = get_here_doc(list->command[i + 1], list);
	if (list->fd[0] == -1 || list->fd[1] == -1)
		return (throw_fd_error(list, i));
	if (list->number <= 3 && list->type[0] >= REDIRECT_RIGHT
		&& list->type[0] <= REDIRECT_AND_APPEND)
		procedure_first_red(list);
	else
		procedure_repoints(list, i);
	return (0);
}

// int main()
// {
// 	t_list_commands list;

// 	list.fd[0] = 0;
// 	list.fd[1] = 1;

// 	get_fd_right_redirects(&list, "1", REDIRECT_RIGHT);
// 	ft_putstr(list.fd[1], "hello");
// }
