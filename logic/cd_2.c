#include "../logic/logic.h"

char	*not_specidied_cd(t_list_commands *cmd)
{
	char	*new_path;

	new_path = cmd->command[1];
	if (chdir(new_path) == -1)
	{
		g_error_code = errno;
		cd_errors(new_path);
	}
	return (new_path);
}


char	*cd_other_paths(t_list_commands *cmd, char *new_path)
{
	if(cmd->command[1][0] == '~')
	{
		cmd->command[1] = ft_strtrim(cmd->command[1], "~/");
		new_path = get_env_var_value(cmd->env_vars, "HOME");
		new_path = ft_strjoin(new_path, cmd->command[1]);
		if (chdir(new_path) == -1)
		{
			g_error_code = errno;
			cd_errors(new_path);
		}
	}
	else if(!ft_strncmp(cmd->command[1], "./", 2))
	{
		cmd->command[1] = ft_strtrim(cmd->command[1], "./");
		new_path = get_env_var_value(cmd->env_vars, "PWD");
		new_path = ft_strjoin(new_path, cmd->command[1]);
		if (chdir(new_path) == -1)
		{
			g_error_code = errno;
			cd_errors(new_path);
		}
	}
	else
		new_path = not_specidied_cd(cmd);
	return (new_path);
}