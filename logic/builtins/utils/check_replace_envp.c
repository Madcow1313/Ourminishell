#include "../logic/logic.h"

//counts double array's len(not str len)
int count_env_len(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static char **join_ostatok(char **old, char **new, int len)
{
	int old_len;
	char **filled_env;
	int i;
	int j;

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
		filled_env[i] = ft_strdup(old[i]);
	j = -1;
	while(++j < len && i < (len + old_len + 1))
	{
		//printf("%s\n", new[j]);
		if (new[j])
		{
			filled_env[i] = ft_strdup(new[j]);
			i++;
		}
	}
	filled_env[i] = NULL;
	return (filled_env);
}

static void do_replace(char **old, char **new)
{
	//printf("I'm your replacement = %s\n", *new);
	//printf("I'm what has been replaced = %s\n", *old);
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
	//printf("No sega\n");
	if (!ft_strncmp(cmp, cmp_2, ft_strlen(cmp_2)))
	{
		if ((*new_env)[k] == '\0')
			free(*new_env);
		else
			do_replace(old_env, new_env);
	}
	//printf("i'm after comparing new %s\n", *new_env);
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

	i = -1;
	j = -1;
	while(++j < len)
		printf("%s\n", new_env[j]);
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
				parts_to_compare(&old_env[i], &new_env[j], k);
			}
		}
	}
	while(old_env[++j])
		printf("%s\n", old_env[j]);
	result = join_ostatok(old_env, new_env, len);
	free_array(new_env);
	free_array(old_env);
	return (result);
}
