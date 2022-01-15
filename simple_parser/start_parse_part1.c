#include "../simple_parser/parser.h"
#include "../logic/logic.h"
/*no double free*/
int	proc_quotes(t_list_commands *list)
{
	char	*temp;

	if (list->type[list->number - 1] == DOUBLE_QM)
	{
		while (ft_strchr_for_dq(list->command[list->number - 1], '$')
			>= 0)
		{
			if (ft_strchr_parser(list->command[list->number - 1], '$')
				== (int)ft_strlen(list->command[list->number - 1]) - 1)
			{
				temp = list->command[list->number];
				list->command[list->number] = ft_strdup("");
				if (!list->command[list->number])
					return (0);
				list->type[list->number] = DOUBLE_QM;
				list->number += 1;
				list->command[list->number] = NULL;
				break ;
			}
			temp = list->command[list->number - 1];
			list->command[list->number - 1]
				= get_prefix_for_env(
					list->env_vars, list->command[list->number - 1]);
			free (temp);
		}
	}
	return (1);
}

int	proc_envp(t_list_commands *list)
{
	char	*temp;

	if (list->command[list->number - 1][0] != '\''
	&& list->command[list->number - 1][0] != '\"'
	&& ft_strlen(list->command[list->number - 1]) > 1)
	{
		temp = list->command[list->number - 1];
		list->command[list->number - 1]
			= get_env_var_value(
				list->env_vars, list->command[list->number - 1] + 1);
		if (!list->command[list->number - 1])
			return (0);
		/*no double free*/
		free (temp);
	}	
	return (1);
}

int	new_alloc_for_f_env(t_list_commands *list, t_command *command)
{
	int		j;
	int		counter;

	counter = 0;
	j = 0;
	while (list->command[0][j])
	{
		if (list->command[0][j] == ' ')
			counter++;
		j++;
	}
	list->command
		= malloc(sizeof(char *) * (command->len + 1)
			+ sizeof(char *) * (counter * 2 + 1));
	list->type
		= malloc(sizeof(int *) * (command->len + 1)
			+ sizeof(int *) * (counter * 2 + 1));
	if (!list->command || !list->type)
		return (0);
	return (1);
}

int	proc_first_env(t_list_commands *list, char **split_string)
{
	int	j;

	j = 0;
	while (split_string[j])
	{
		list->command[list->number] = ft_strdup(split_string[j]);
		if (!list->command[list->number])
			return (0);
		list->type[list->number] = BUILT_IN;
		list->number += 1;
		list->command[list->number] = malloc(1);
		if (!list->command[list->number])
			return (0);
		list->command[list->number][0] = '\0';
		list->type[list->number] = SEP_SPACE;
		list->number += 1;
		list->command[list->number] = NULL;
		j++;
	}
	return (1);
}

int	proc_space(t_list_commands *list)
{
	list->command[list->number] = malloc(1);
	if (!list->command[list->number])
		return (0);
	list->command[list->number][0] = '\0';
	list->type[list->number] = SEP_SPACE;
	list->number += 1;
	list->command[list->number] = NULL;
	return (1);
}

int	check_first_cmd(t_list_commands *list, t_command *command)
{
	int		j;
	int		*temp2;
	char	**split_string;
	char	*temp4;
	char	**temp3;

	list->number = 0;
	j = 0;
	split_string = ft_split(list->command[0], ' ');
	if (!split_string)
		return (0);
	temp2 = list->type;
	temp3 = list->command;
	temp4 = list->command[0];
	new_alloc_for_f_env(list, command);
	proc_first_env(list, split_string);
	free (temp4);
	free (temp2);
	free (temp3);
	while (split_string[j])
		if (split_string[j])
			free (split_string[j++]);
	free (split_string);
	return (1);
}

int	start_all(t_list_commands *list, t_command *command, size_t *i, int ret)
{
	list->type[list->number] = search_for_type(command, *i);
	if (list->type[list->number] == BUILT_IN)
		ret = get_built_in_cmd(command, list, i);
	else if (list->type[list->number] == PIPE
		|| list->type[list->number] == SEMICOLON)
	{
		ret = get_pipe(list, list->type[list->number]);
		*i += 1;
	}
	else if (list->type[list->number] == SINGLE_QM
		|| list->type[list->number] == DOUBLE_QM)
	{
		ret = handle_quotes(list, command, list->type[list->number], i);
		ret = proc_quotes(list);
		*i += 1;
	}
	else if (list->type[list->number] >= REDIRECT_RIGHT
		&& list->type[list->number] <= REDIRECT_AND_APPEND)
			ret = handle_redirects(list, list->type[list->number], i);
	else if (list->type[list->number] == ENVIRONMENT_VAR)
	{
		get_built_in_cmd(command, list, i);
		proc_envp(list);
	}
	return (ret);
}

t_list_commands	*start_parse(t_command *command, t_list_commands *list)
{
	size_t	i;
	int		ret;

	i = 0;
	while (i < command->len && command->word[i] != '\0')
	{
		ret = start_all(list, command, &i, ret);
		if (list->number == 1 && list->type[0] == ENVIRONMENT_VAR && ret)
			ret = check_first_cmd(list, command);
		if (command->word[i] == ' ' && ret)
			ret = proc_space(list);
		else if (ret)
			continue ;
		if (!ret)
			return (list);
		while (command->word[i] == ' ')
			i++;
	}
	return (list);
}
