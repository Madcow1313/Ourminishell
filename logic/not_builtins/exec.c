#include "../logic/logic.h"

char	**path_directories()
{
	char	**path;
	char	*env_var;

	env_var = getenv("PATH");
	if (!env_var)
		return (NULL);
	path = ft_split(env_var, ':');
	return (path);
}

int	open_next_dir(t_opendir *o_dir)
{
	o_dir->i++;
	if (o_dir->path[o_dir->i])
		opendir(o_dir->path[o_dir->i]);
	if (o_dir->dir == NULL)
	{
		g_error_code = errno;
		return (-1);
	}
	return (o_dir->i);
}

char	*get_binary_from_path(t_list_commands *cmd, t_opendir *o_dir)
{
	o_dir->i = 0;
	o_dir->path = path_directories();
	o_dir->dir = opendir(o_dir->path[o_dir->i]);
	if (o_dir->dir == NULL)
	{
		g_error_code = errno;
		return (NULL);
	}
	o_dir->name = readdir(o_dir->dir);
	while(o_dir->i <= count_env_len(o_dir->path) && o_dir->path[o_dir->i])
	{
		if (o_dir->name == NULL)
		{
			o_dir->i = open_next_dir(o_dir);
			if (o_dir->i == -1)
				break ;
			o_dir->name = readdir(o_dir->dir);
			continue ;
		}
		if(!ft_strncmp(cmd->command[0], o_dir->name->d_name, ft_strlen(o_dir->name->d_name)))
		{
			o_dir->file_path = ft_strjoin(o_dir->path[o_dir->i], "/");
			o_dir->file_path = ft_strjoin(o_dir->file_path, o_dir->name->d_name);
			free_array(o_dir->path);
			closedir(o_dir->dir);
			return (o_dir->file_path);
		}
		o_dir->name = readdir(o_dir->dir);
	}
	if (closedir(o_dir->dir) == -1)
		g_error_code = errno;
	free_array(o_dir->path);
	return(NULL);
}

void	command_error(t_list_commands *cmd)
{
	g_error_code = 1;
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(cmd->command[0], 2);
	ft_putstr_fd(" ", 2);
	errors();
	return ;
}

void	exec(t_list_commands *cmd, t_opendir *open_dir)
{
	pid_t	pid;
	char	*file_path;

	for(int i = 0; cmd->command[i]; i++)
		printf("i got = %s\n", cmd->command[0]);
	file_path = get_binary_from_path(cmd, open_dir);
	//printf("%s\n", file_path);
	pid = fork();
	if (pid == 0)
	{
		if (execve(file_path, cmd->command, cmd->env_vars) == -1)
			{
				g_error_code = errno;
				ft_putstr_fd("Error: ", 2);
				ft_putstr_fd(cmd->command[0], 2);
				ft_putstr_fd(" ", 2);
				errors();
				return ;
			}
		g_error_code = 0;
	}
	else if (pid > 0)
		wait(&pid);
	else
		ft_putstr_fd("Can't execute command, fork failed\n", 2);
	free(file_path);
}
