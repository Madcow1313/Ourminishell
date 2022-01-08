#include "../logic/logic.h"

int	find_equal_sign(char *s)
{
	int	i;

	i = -1;
	while(s[++i])
	{
		if(s[i] == '=')
			return (0);
	}
	return (1);
}

static char	**check_valid_unset(t_list_commands *cmd)
{
	int		i;
	char	**new_env;
	int		len;
	
	i = 1;
	len = 0;
	while(cmd->command[i])
	{
		if (!wrong_symbols(cmd->command[i]) || !find_equal_sign(cmd->command[i]))
		{
			export_errors(cmd->command[i]);
			i++;
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

int	util_to_cmpr_old_and_set(char **old, char *set)
{
	int		i;
	char	*cmp;

	i = 0;
	while ((*old)[i] && (*old)[i] != '=')
		i++;
	cmp = ft_substr(*old, 0, i);
	if (!ft_strncmp(set, cmp, ft_strlen(cmp)))
		return (0);
	return (1);
}

static char	**remove_env(char **old, char **unset_env, char *set)
{
	int	old_len;
	int	i;
	int	j;

	i = -1;
	j = 0;
	old_len = count_env_len(old);
	if (unset_env)
		free_array(unset_env);
	unset_env = malloc(sizeof(char*) * (old_len + 1));
	while(old[++i])
	{
		if (!util_to_cmpr_old_and_set(&old[i], set))
			i++;
		unset_env[j] = ft_strdup(old[i]);
		j++;
	}
	unset_env[j] = NULL;
	return (unset_env);
}

static char	**parts_to_compare_unset(char **old_env, char **set, char **full_old_env, char **unset)
{
	char	*cmp_2;
	char	*tmp_set;
	int		i;

	i = 0;
	tmp_set = *set;
	if (!*set || !*old_env)
		return (old_env);
	while ((*old_env)[i] && (*old_env)[i] != '=')
		i++;
	cmp_2 = ft_substr(*old_env, 0, i);
	if (!ft_strncmp(tmp_set, cmp_2, ft_strlen(cmp_2)))
		unset = remove_env(full_old_env, unset, tmp_set);
	free(cmp_2);
	return (unset);
}

static char	**unset_env(char **old_env, char **set, int len)
{
	int		i;
	int		j;
	int		k;
	char	**unset;
	
	i = -1;
	unset = NULL;
	while (old_env[++i])
	{
		j = -1;
		while (++j < len && set[j])
		{
			if(set[j])
			{
				k = 0;
				while (old_env[j][k] != '=')
					k++;
				unset = parts_to_compare_unset(&old_env[i], &set[j], old_env, unset);
			}
		}
	}
	if (!unset)
		return (old_env);
	return (unset);
}

static char **deleting_new_env_var(t_list_commands *cmd)
{
	char	**new_env;
	int		env_len;
//	int i;

	new_env = check_valid_unset(cmd);
	if (new_env == NULL)
		return (cmd->env_vars);
	/* for (i = 0; new_env[i]; i++)
		printf("%s\n", new_env[i]); */
	env_len = count_env_len(new_env);
	cmd->env_vars = unset_env(cmd->env_vars, new_env, env_len);
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
