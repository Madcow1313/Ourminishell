#include "../logic/logic.h"

char	**free_array(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);

	while (env[i])
	{
		free (env[i]);
		printf("%d\n", i);
		i++;
	}
	free(env);
	env = NULL;
	return (env);
}

char	**init_new_env(int len)
{
	char	**new_env;

	if (!len)
	{
		new_env = NULL;
		return (new_env);
	}
	new_env = malloc(sizeof(char*) * (len + 1));
	if (!new_env)
		malloc_error(new_env);
	return (new_env);
}

char	**alloc_and_fill_new_env(t_list_commands *cmd, char **new_env)
{
	int	i;
	int	id;
	
	i = 0;
	id = 0;
	while(cmd->command[++i])
	{
		if (!check_first_symbol(cmd->command[i][0]) || !wrong_symbols(cmd->command[i]))
			continue ;
		new_env[id] = ft_strdup(cmd->command[i]);
		if (!new_env[id])
		{	
			malloc_error(new_env);
			return (NULL);
		}
		id++;
	}
	new_env[id] = NULL;
	return (new_env);
}

char	**check_valid_envp(t_list_commands *cmd)
{
	int		i;
	char	**new_env;
	int		len;
	
	i = 1;
	len = 0;
	while(cmd->command[i])
	{
		if (!check_first_symbol(cmd->command[i][0])
			|| !wrong_symbols(cmd->command[i]))
		{
			export_errors(cmd->command[i]);
			i++;
			continue ;
		}
		if (cmd->command[i])
		{
			i++;
			len++;
		}
	}
	new_env = init_new_env(len);
	if (!new_env)
		return(NULL);
	new_env = alloc_and_fill_new_env(cmd, new_env);
	return (new_env);
}
