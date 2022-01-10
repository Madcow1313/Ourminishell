#include "../logic/logic.h"

char	**fill_unset(char **old, int old_len, int final_len)
{
	char	**result;
	int		i;
	int		j;

	result = malloc(sizeof(char *) * (final_len + 1));
	if (!result)
	{
		malloc_error(result);
		return(old);
	}
	i = -1;
	j = 0;
	while (++i <= old_len)
	{
		if (old[i])
		{
			result[j] = old[i];
			j++;
		}
	}
	printf("result[j] = %s\n", result[j]);
	result[j] = NULL; //or j+1?
	free(old);
	old = NULL;
	return(result);
}

static void	parts_to_compare_unset(char **old_env, char **set)
{
	char	*cmp;
	char	*tmp_set;
	int		i;

	i = 0;
	tmp_set = *set;
	if (!*set || !*old_env || !set || !old_env)
		return ;
	while ((*old_env)[i] && (*old_env)[i] != '=')
		i++;
	cmp = ft_substr(*old_env, 0, i);
	if (!ft_strncmp(tmp_set, cmp, ft_strlen(cmp)))
	{
		if (*old_env && old_env)
			free(*old_env);
		*old_env = NULL;
	}
	free(cmp);
	return ;
}

static char	**unset_env(char **old_env, char **set, int len, int old_len)
{
	int		i;
	int		j;
	int		k;
	char	**unset;
	int		len_after_unset;
	
	i = -1;
	while (old_env[++i] && i <= old_len)
	{
		j = -1;
		while (++j <= len)
		{
			if(set[j])
			{
				k = 0;
				if (old_env[i])
					while (old_env[i][k] != '=')
						k++;
				parts_to_compare_unset(&old_env[i], &set[j]);
			}
		}
	}
	i = -1;
	len_after_unset = 0;
	while (++i <= old_len)
		if (old_env[i])
			len_after_unset++;
	//for (int j = 0; j <= old_len; j++)
	//	printf("old_env[j] after unset = %s\n", old_env[j]);
	unset = fill_unset(old_env, old_len, len_after_unset);
	if (!unset)
		return (old_env);
	return (unset);
}

static char **deleting_new_env_var(t_list_commands *cmd)
{
	char	**new_env;
	int		unset_len;
	int		old_len;

	new_env = check_valid_unset(cmd);
	if (new_env == NULL)
		return (cmd->env_vars);
	for (int i = 0; new_env[i]; i++)
		printf("%s\n", new_env[i]);
	unset_len = count_env_len(new_env);
	old_len = count_env_len(cmd->env_vars);
	//while(1);
	cmd->env_vars = unset_env(cmd->env_vars, new_env, unset_len, old_len);
	free_array(new_env);
	return (cmd->env_vars);
}

void	process_unset(t_list_commands *cmd)
{
	// printf("no sega\n");
	// printf("\n");
	// for (int i = 0; cmd->env_vars[i]; i++)
	// 	printf("%s\n", cmd->env_vars[i]);
	// printf("\n");
	if (cmd->command[1])
		cmd->env_vars = deleting_new_env_var(cmd);
	return ;
}
