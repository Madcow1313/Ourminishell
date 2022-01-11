#include "../logic/logic.h"

char	**path_directories(t_list_commands *cmd)
{
	int	i;
	char	**path;
	char	*env_var;

	i = 0;
	while (cmd->env_vars[i])
	{
		if (!ft_strncmp(cmd->env_vars[i], "PATH", ft_strlen("PATH")))
			break ;
		i++;
	}
	env_var = getenv("PATH");
	path = ft_split(env_var, ':');
	return (path);
}

char	*get_binary_from_path(t_list_commands *cmd)
{
	char			**path;
	DIR				*dir;
	int				i;
	struct dirent	*name;
	char			*file_path;

	i = 0;
	path = path_directories(cmd);
	dir = opendir(path[0]);
	if (dir == NULL)
		return (NULL);
	name = readdir(dir);
	while(path[i])
	{
		if (name == NULL)
		{
			i++;
			closedir(dir);
			dir = opendir(path[i]);
			name = readdir(dir);
			continue ;
		}
		if(!ft_strncmp(cmd->command[i], name->d_name, ft_strlen(cmd->command[i])))
		{
			file_path = ft_strjoin(path[i], name->d_name);
			free_array(path);
			closedir(dir);
			return (file_path);
		}
		printf("name is = %s\n", name->d_name);
		name = readdir(dir);
	}
	return(NULL);
}

//i need to GET COMMAND PAAATH FROM PATH VARIABLE to get binary
//so i need to open and search each folder in PATH if it contains file named "ls" (f.e) or nah
void	exec(t_list_commands *cmd)
{
	pid_t	pid;
	char	*file_path;

	file_path = get_binary_from_path(cmd);
	pid = fork();
	if (pid == 0)
	{
		if (execve(file_path, cmd->command, cmd->env_vars) == -1)
			{
				g_error_code = errno;
				ft_putstr_fd("Error: ", 2);
				ft_putstr_fd(file_path, 2);
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