#include "../logic/logic.h"

char	**fill_unset(char **old, int old_len)
{
	char	**result;
	int		i;
	int		j;

	result = malloc(sizeof(char *) * (old_len + 1));
	if (!result)
	{
		malloc_error(result);
		return(old);
	}
	i = -1;
	j = 0;
<<<<<<< HEAD
	while (++i < old_len)
	{
		if (old[i])
		{
			result[j] = ft_strdup(old[i]);
			j++;
		}
=======
	old_len = count_env_len(old);
	if (unset_env)
		free_array(unset_env);
	unset_env = malloc(sizeof(char*) * (old_len + 1));
	while(old[i] && old[++i])
	{
		if (!util_to_cmpr_old_and_set(&old[i], set) && old[i])
			i++;
		unset_env[j] = ft_strdup(old[i]);
		j++;
>>>>>>> 0499986547cb2633d8ad4b97747cde207a6f1ae0
	}
	result[j] = NULL;
	return(result);
}

static void	parts_to_compare_unset(char **old_env, char **set)
{
	char	*cmp_2;
	char	*tmp_set;
	int		i;

	i = 0;
	tmp_set = *set;
	if (!*set || !*old_env || !set || !old_env)
		return ;
	while ((*old_env)[i] && (*old_env)[i] != '=')
		i++;
	cmp_2 = ft_substr(*old_env, 0, i);
	if (!ft_strncmp(tmp_set, cmp_2, ft_strlen(cmp_2)))
	{
		if (*old_env && old_env)
			free(*old_env);
		*old_env = NULL;
	}
	free(cmp_2);
	return ;
}

static char	**unset_env(char **old_env, char **set, int len, int old_len)
{
	int		i;
	int		j;
	int		k;
	char	**unset;
	
	i = -1;
	while (old_env[++i])
	{
		j = -1;
		while (++j < len)
		{
			if(set[j])
			{
				k = 0;
				while (old_env[j][k] != '=')
					k++;
				parts_to_compare_unset(&old_env[i], &set[j]);
			}
		}
	}
	unset = fill_unset(old_env, old_len);
	if (!unset)
		return (old_env);
	//free(old_env);
	return (unset);
}

static char **deleting_new_env_var(t_list_commands *cmd)
{
	char	**new_env;
	int		env_len;
	int		old_len;

	new_env = check_valid_unset(cmd);
	if (new_env == NULL)
		return (cmd->env_vars);
	for (int i = 0; new_env[i]; i++)
		printf("%s\n", new_env[i]);
	env_len = count_env_len(new_env);
	old_len = count_env_len(cmd->env_vars);
	cmd->env_vars = unset_env(cmd->env_vars, new_env, env_len, old_len);
	free_array(new_env);
	return (cmd->env_vars);
}

void	process_unset(t_list_commands *cmd)
{
	printf("no sega\n");
	if (cmd->command[1])
		cmd->env_vars = deleting_new_env_var(cmd);
	return ;
}
