#include "../logic/logic.h"

int	count_env_len(char **env)
{
	int	i;

	i = 0;
	while(env[i])
		i++;
	return (i);
}

static int	do_replace(char *old, char *new, int len)
{
	free(old);
	old = ft_strdup(new);
	free(new);
	len--;
	return (len);
}

static char	**join_ostatok(char **old, char **new, int len)
{
	int		old_len;
	char	**filled_env;
	int		i;
	int		j;

	if (!len)
	{
		if (new)
			free_array(new);
		return (NULL);
	}
	old_len = count_env_len(old);
	filled_env = malloc(sizeof(char *) * (len + old_len + 1));
	if (!filled_env)
		malloc_error(filled_env);
	i = -1;
	while(old[++i])
		filled_env[i] = ft_strdup(old[i]);
	j = -1;
	while (++j < len)
	{
		if (new[j] == NULL)
			j++;
		filled_env[i] = ft_strdup(new[j]);
	}
	filled_env[i] = NULL;
	return (filled_env);
}

char	**check_replace_env(char **old_env, char **new_env, int len)
{
	int	i;
	int	j;
	int	k;
	char	*cmp;
	char	**result;

	i = 0;
	printf("what is going on\n");
	while(old_env[i])
	{
		j = 0;
		while (new_env[j])
		{
			k = 0;
			while(new_env[j] && new_env[j][k] != '=')
				k++;
			cmp = ft_substr(new_env[j], 0, k);
			printf("%s\n", cmp);
			if (!ft_strncmp(cmp, old_env[i], ft_strlen(cmp)))
			{
				if (new_env[j][k + 2] != '\0')
					len = do_replace(old_env[i], new_env[j], len);
			}
			free(cmp);
			j++;
		}
		i++;
	}
	result = join_ostatok(old_env, new_env, len);
	free_array(new_env);
	free_array(old_env);
	return (result);
}
