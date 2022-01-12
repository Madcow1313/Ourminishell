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

static struct dirent	*next_dir(t_opendir *o_dir)
{
	o_dir->i++;
	if (o_dir->path[o_dir->i])
	{
		o_dir->dir = opendir(o_dir->path[o_dir->i]);
		if (o_dir->dir == NULL)
		{
			g_error_code = errno;
			return (NULL);
		}
		o_dir->name	= readdir(o_dir->dir);
	}
	return (o_dir->name);
}

static char	*fill_path(t_opendir *o_dir)
{
	char	*path;

	path = ft_strjoin(o_dir->path[o_dir->i], "/");
	o_dir->file_path = ft_strjoin(path, o_dir->name->d_name);
	free(path);
	//free_array(o_dir->path);
	//if (closedir(o_dir->dir) == -1)
	//	g_error_code = errno;
	return (o_dir->file_path);
}

char	*reading_directories(t_list_commands *cmd, t_opendir *o_dir)
{
	int	path_len;

	path_len = count_env_len(o_dir->path);
	while(o_dir->i <= path_len && o_dir->path[o_dir->i])
	{
		if (o_dir->name == NULL)
		{
			if(!o_dir->path[o_dir->i])
				break ;
			o_dir->name = next_dir(o_dir);
			continue ;
		}
		if (!ft_cmprcmd(cmd->command[0], o_dir->name->d_name))
		{
			o_dir->file_path = fill_path(o_dir);
			return (o_dir->file_path);
		}
		o_dir->name = readdir(o_dir->dir);
	}
	return (NULL);
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
	o_dir->file_path = reading_directories(cmd, o_dir); 
	if (closedir(o_dir->dir) == -1)
		g_error_code = errno;
	free_array(o_dir->path);
	while (1);
	return(o_dir->file_path);
}
