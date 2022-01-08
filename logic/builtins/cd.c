#include "../logic/logic.h"

void dup_and_free_new_paths(t_list_commands *cmd, char *buf, int i)
{
	free(cmd->env_vars[i]);
	cmd->env_vars[i] = ft_strdup(buf);
	free(buf);
}

void set_pwd(t_list_commands *cmd)
{
	char *buf;
	char *old_pwd;
	int i;

	i = -1;
	cmd->env_vars = find_old_pwd(cmd);
	old_pwd = ft_strjoin("OLDPWD=", get_env_var_value(cmd->env_vars, "PWD"));
	//	printf("%s\n", old_pwd);
	buf = ft_strjoin("PWD=", getcwd(NULL, 0));
	//	printf ("%s\n", buf);
	while (cmd->env_vars[++i])
	{
		if (!ft_strncmp(cmd->env_vars[i], "PWD", ft_strlen("PWD")))
			dup_and_free_new_paths(cmd, buf, i);
		if (!ft_strncmp(cmd->env_vars[i], "OLDPWD", ft_strlen("OLDPWD")))
			dup_and_free_new_paths(cmd, old_pwd, i);
	}
}

static void cd_to_home_dir(t_list_commands *cmd)
{
	char *home_path;

	home_path = get_env_var_value(cmd->env_vars, "HOME");
	if (chdir(home_path) == -1)
	{
		g_error_code = errno;
		cd_errors(home_path);
	}
	return;
}

static void cd_has_path(t_list_commands *cmd)
{
	char *new_path;

	new_path = ft_strdup(cmd->command[1]);
	if (chdir(new_path) == -1)
	{
		g_error_code = errno;
		cd_errors(new_path);
	}
	free(new_path);
	return;
}

void process_cd(t_list_commands *cmd)
{
	if (cmd->command[1] != NULL)
		cd_has_path(cmd);
	else
		cd_to_home_dir(cmd);
	set_pwd(cmd);
	g_error_code = 0;
	return;
}
