#include "../logic/logic.h"

//counts double array's len(not str len)
int count_env_len(char **env)
{
	int i;

	i = 0;
	/*i changed to -1 . Bulat*/
	/*changed back*/
	while (env[i])
		i++;
	return (i);
}

static char **join_ostatok(char **old, char **new, int len)
{
	int		old_len;
	char	**filled_env;
	int		i;
	int		j;

	if (!len || new == NULL)
		return (old);
	old_len = count_env_len(old);
	filled_env = malloc(sizeof(char *) * (len + old_len + 1));
	if (!filled_env)
	{
		malloc_error(filled_env);
		return (old);
	}
	i = -1;
	while(old[++i])
		filled_env[i] = old[i]; //look here
	free(old); //look here
	old = NULL; //look here
	j = -1;
	while(++j < len)
	{
		if (new[j])
		{
			filled_env[i] = ft_strdup(new[j]);
			printf("here ? %s\n", filled_env[i]);
			i++;
		}
	}
	filled_env[i] = NULL;
	return (filled_env);
}

static void do_replace(char **old, char **new)
{
	if(*old)
		free(*old);
	*old = ft_strdup(*new);
	free(*new);
	*new = NULL;
	return;
}

static void parts_to_compare(char **old_env, char **new_env, int k)
{
	char *cmp;
	char *cmp_2;
	int i;

	i = 0;
	if(!*new_env || !*old_env)
		return ;
	cmp = ft_substr(*new_env, 0, k);
	while ((*old_env)[i] && (*old_env)[i] != '=')
		i++;
	cmp_2 = ft_substr(*old_env, 0, i);
	if (!ft_strncmp(cmp, cmp_2, ft_strlen(cmp_2)))
	{
		if ((*new_env)[k] == '\0' && *new_env)
		{
			free(*new_env);
			*new_env = NULL;
		}
		else
			do_replace(old_env, new_env);
	}
	free(cmp_2);
	free(cmp);
	return;
}

char **check_replace_env(char **old_env, char **new_env, int len)
{
	int		i;
	int		j;
	int		k;
	char	**result;
	int		len_after_check_replace;

	i = -1;
	while (old_env[++i])
	{
		j = -1;
		while (++j < len)
		{
			if(new_env[j])
			{
				k = 0;
				while (new_env[j][k] && new_env[j][k] != '=')
					k++;
				if (new_env[j])
					parts_to_compare(&old_env[i], &new_env[j], k);
			}
		}
	}
	i = -1;
	len_after_check_replace = 0;
	while(++i < len) //delete printf after
		if (new_env[i])
			{len_after_check_replace++; printf("new_env[i] after replace = %s\n", new_env[i]);}
	printf("len aftercheck replace = %d\n", len_after_check_replace);
	result = join_ostatok(old_env, new_env, len_after_check_replace);
	return (result);
}
