#include "../logic/logic.h"

static char	**create_old_pwd(char **new_env, t_list_commands *cmd, int len)
{
	int	i;

	i = -1;
	new_env = malloc(sizeof(char*) *(len + 2));
	if (!new_env)
	{
		malloc_error(new_env);
		return (cmd->env_vars);
	}
	i = -1;
	while(cmd->env_vars[++i])
		new_env[i] = ft_strdup(cmd->env_vars[i]);
	new_env[i] = ft_strdup("OLDPWD=");
	i++;
	new_env[i] = NULL;
	free_array(cmd->env_vars);
	return(new_env);
}

char	**find_old_pwd(t_list_commands *cmd)
{
	int		i;
	char	**new_env;
	int		len;

	i = -1;
	new_env = NULL;
	len = count_env_len(cmd->env_vars);
	while(cmd->env_vars[++i])
	{
		if (!ft_strncmp(cmd->env_vars[i], "OLDPWD", ft_strlen("OLDPWD")))
			return (cmd->env_vars);
	}
	new_env = create_old_pwd(new_env, cmd, len);
	return(new_env);
}
