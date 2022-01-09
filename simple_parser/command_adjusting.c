#include "parser.h"

/*delete this, if no use*/
int	count_slashes(char *string, int i)
{
	int	counter;

	counter = 0;
	while (string[i] && string[i++] == '\\')
		counter++;
	return (counter);
}

/*a bit clunky, but works, i believe*/
char	*delete_a_char(char *string)
{
	char	*new_string;
	char	*temp;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	new_string = malloc(sizeof(string));
	if (!new_string)
		return (NULL);
	temp = string;
	while (string[i] && temp[i])
	{
		while ((string[i] != '\'' && string[i] != '\"') && string[i])
		{
			new_string[j] = string[i];
			j++;
			i++;
		}
		c = string[i];
		i++;
		while (string[i] != c && string[i])
		{
			new_string[j] = string[i];
			j++;
			i++;
		}
	}
	new_string[j] = '\0';
	return (new_string);
}

/*something is wrong with memory, of course leaks*/
int	delete_quotes(t_list_commands *list)
{
	int		i;

	i = 0;
	while (list->command[i])
	{
		if (list->type[i] == BUILT_IN || list->type[i] == WORD
			|| list->type[i] == ENVIRONMENT_VAR)
		{
			if (find_first_qm(list->command[i]) < ft_strlen(list->command[i]))
			{
				list->command[i] = delete_a_char(list->command[i]);
				if (!list->command[i])
					return (0);
			}
		}	
		i++;
	}
	return (1);
}

/*i guess no leaks, delete some stuff, add isalnum*/
char	*get_env_var_value(char **env_vars, char *string)
{
	char	*temp;
	char	*new_string;
	int		size;
	int		i;

	i = 0;
	size = 0;
	temp = string;
	if (string[i] == '\'' || string[i] == '\"')
		return (string);
	if (string[i] == '?')
		return (ft_strjoin("?", string + 1));
	while (string[i] && ((string[i] >= 'a' && string[i] <= 'z')
			|| (string[i] >= '0' && string[i] <= '9')
			|| (string[i] >= 'A' && string[i] <= 'Z')))
	{
		i++;
		size++;
	}
	if (size == 0)
		return (string - 1);
	temp += i;
	i = 0;
	while (env_vars[i])
	{
		if (!ft_strncmp(env_vars[i], string, size))
		{
			if (env_vars[i][size] == '=')
			{
				string = env_vars[i] + size + 1;
				new_string = ft_strjoin(string, temp);
				return (new_string);
			}
		}
		i++;
	}
	string = "";
	new_string = ft_strjoin(string, temp);
	return (new_string);
}

char	*get_prefix_for_env(char **env_vars, char *string)
{
	char	*temp;
	char	*temp2;
	char	*new_string;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (string[i] != '$' && string[i])
	{
		i++;
		size++;
	}
	temp = malloc(size + 1);
	i = 0;
	ft_strlcpy(temp, string, size + 1);
	temp2 = get_env_var_value(env_vars, (string + size + 1));
	new_string = ft_strjoin(temp, temp2);
	return (new_string);
}