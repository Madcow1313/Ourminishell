#include "../logic/logic.h"

char	*cd_to_home_dir(t_list_commands *cmd)
{
	char	*home_path;

	home_path = get_env_var_value(cmd->env_vars, "HOME");
	if (chdir(home_path) == -1)
	{
		g_error_code = errno;
		cd_errors(home_path);
	}
	return (home_path);
}

char	*process_relative_path(t_list_commands *cmd)
{
	char	*new_path = NULL;

	if (cmd->command[1][0] == '-')
	{
		new_path = get_env_var_value(cmd->env_vars, "OLDPWD");
		if (chdir(new_path) == -1)
		{
			g_error_code = errno;
			cd_errors(new_path);
		}
	}
	else if (!(ft_strncmp(cmd->command[1], "..", 2)))
	{
		cmd->command[1] = ft_strtrim(cmd->command[1], "../");
		new_path = get_env_var_value(cmd->env_vars, "HOME");
		new_path = ft_strjoin(new_path, cmd->command[1]);
		if (chdir(new_path) == -1)
		{
			g_error_code = errno;
			cd_errors(new_path);
		}
	}
	else
		new_path = cd_other_paths(cmd, new_path);
	return (new_path);
}

char	*cd_has_path(t_list_commands *cmd)
{
	char	*new_path = NULL;

	if (cmd->type[1] == 13)
	{
		new_path = cmd->command[1];
		if (chdir(new_path) == -1)
		{
			g_error_code = errno;
			cd_errors(new_path);
		}
	}
	else if (cmd->type[1] == 14)
		new_path = process_relative_path(cmd);
	return (new_path);
}

void	process_cd(t_list_commands *cmd)
{
	char	*new_path;

	if (cmd->command[1] != NULL)
		new_path = cd_has_path(cmd);
	else
	{
		new_path = cd_to_home_dir(cmd);
	}
	g_error_code = 0;
	(void)new_path;
	return ;
}