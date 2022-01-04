#include "parser.h"

void	get_here_doc(char *end, t_list_commands *list)
{
	char	*line;
	int		fd;

	fd = open(".here_doc_minishell", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	while (1)
	{
		line = readline(">");
		line = get_prefix_for_env(list->env_vars, line);
		if (!ft_strncmp(line, end, ft_strlen(line)) && ft_strlen(line) > 0)
		{
			free (line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}



void	ft_putstr(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

/*i have no idea what should i do
still in progress*/
int	get_fd_left_redirects(t_list_commands *list, char *path, int type)
{
	int	fd_to_apply;

	fd_to_apply = 0;
	if (type == REDIRECT_LEFT)
	{
		fd_to_apply = open(path, O_RDONLY);
		dup2(fd_to_apply, list->fd[0]);
	}
	return (list->fd[0]);
}

int	get_fd_right_redirects(t_list_commands *list, char *path, int type)
{
	int	fd_to_apply;

	fd_to_apply = 1;
	if (type == REDIRECT_RIGHT)
		fd_to_apply = open(path, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	else if (type == REDIRECT_AND_APPEND)
		fd_to_apply = open(path, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
	printf("fd of file %d\n", fd_to_apply);
	dup2(fd_to_apply, list->fd[1]);
	return (list->fd[1]);
	//close(list->fd[1]);
}

void	set_default_fd(t_list_commands *list)
{
	int	ttyfd;

	ttyfd = open("/dev/tty", O_RDWR);
	dup2(ttyfd, STDOUT_FILENO);
	dup2(ttyfd, STDIN_FILENO);
	close(ttyfd);
	// if (list->fd[0] != 0)
	// {
		//close(list->fd[0]);
		//dup2(list->fd[0], list->old_stdin);
	//}
	// if (list->fd[1] != 1)
	// {
		//close(list->fd[1]);
		dup2(list->fd[1], list->old_stdout);
	//}
}

int	get_redirect_type(t_list_commands *list)
{
	int	i;

	i = 0;
	while (i <= list->number && list->command[i])
	{
		if (list->type[i] == REDIRECT_RIGHT || list->type[i] == REDIRECT_AND_APPEND
			|| list->type[i] == REDIRECT_LEFT || list->type[i] == HERE_DOC)
			return (1);
		i++;
	}
	return (0);
}


char	*repoint(char *string1, char *string2, int *type, int i)
{
	//char	*temp;

	//temp = string1;
	string1 = string2;
	type[i] = type[i + 2];
	//temp = temp;
	return (string1);
}

/*a lot of leaks, should be.
function works next way:
it change arrays
and set list->fd[1] to the last redirected file.
it doesn't close files!!!!*/
int	rid_of_redirect_right(t_list_commands *list)
{
	//char *temp;
	int	i;

	i = 0;
	list->old_stdin = dup(STDIN_FILENO);
	list->old_stdout = dup(STDOUT_FILENO);
	while ((list->type[i] != REDIRECT_RIGHT && list->type[i] != REDIRECT_LEFT && list->type[i] != REDIRECT_AND_APPEND
		&& list->type[i] != HERE_DOC)
		&& list->command[i] && i < list->number)
		i++;
	if (list->type[i + 1] == SEP_SPACE)
		i++;
	if (list->type[i] == REDIRECT_RIGHT || list->type[i] == REDIRECT_AND_APPEND)
		list->fd[1] = get_fd_right_redirects(list, list->command[i + 1], list->type[i]);
	else if (list->type[i] == REDIRECT_LEFT)
		list->fd[0] = get_fd_left_redirects(list, list->command[i + 1], list->type[i]);
	else if (list->type[i] == HERE_DOC)
		get_here_doc(list->command[i + 1], list);
	if (list->command[i])
	{
		if (list->command[i + 1])
		{
			list->command[i] = repoint(list->command[i + 1], list->command[i + 2], list->type, i);
		}
		else
			return (-1);
		if (list->command[i + 1])
		{
			i++;
			while (i <= list->number)
			{
				if (!list->command[i + 2])
				{
					list->command[i] = repoint(list->command[i + 1], NULL, list->type, i);
					break;
				}
				else
				{
					list->command[i] = repoint(list->command[i + 1], list->command[i + 2], list->type, i);
					i++;
				}
			}
		}
	}
	//temp = list->command[list->number - 2];
	//list->command[list->number - 2] = NULL;
	//temp = temp;
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
