#include "parser.h"
#include "../logic/logic.h"

int	define_redirect(t_command *command, int i)
{
	if (command->word[i] == '>')
	{
		if (command->word[i + 1] == '>')
			return (REDIRECT_AND_APPEND);
		else
			return (REDIRECT_RIGHT);
	}
	else
	{
		if (command->word[i + 1] == '<')
			return (HERE_DOC);
		return (REDIRECT_LEFT);
	}
}

/*rignt now ENVIRONMENT_VAR == $, rename*/
int	search_for_type(t_command *command, int i)
{
	if (ft_strchr("><$\'\"|;./", command->word[i]) >= 0)
	{
		if (command->word[i] == '\'')
			return (SINGLE_QM);
		if (command->word[i] == '\"')
			return (DOUBLE_QM);
		if (command->word[i] == '>' || command->word[i] == '<')
			return (define_redirect(command, i));
		if (command->word[i] == '$'
			&& command->word[i] && command->word[i] != ' ')
			return (ENVIRONMENT_VAR);
		else if (command->word[i] == '$')
			return (BUILT_IN);
		if (command->word[i] == ';')
			return (SEMICOLON);
		if (command->word[i] == '|')
			return (PIPE);
	}
	else
		return (BUILT_IN);
	return (BUILT_IN);
}

/*special symbols in first cycle are not working correctly*/
int get_built_in_cmd(t_command *command, t_list_commands *list, size_t *i)
{
	size_t size;

	size = 0;
	while (command->word[*i + size] != ' ' && command->word[*i + size] != '\0'
		&& size <= command->len - *i && command->word[*i + size]
		&& command->word[*i + size] != '>'
		&& command->word[*i + size] != '<'
		&& command->word[*i + size] != '\"'
		&& command->word[*i + size] != '\'')
	{
		if (command->word[*i + size] == '$' && size == 0
			&& command->word[*i + size + 1] != '\"'
			&& command->word[*i + size + 1] != '\'')
			size++;
		else if (command->word[*i + size] == '$')
			break ;
		else
			size++;
	}
	if (size == 0)
	{
		*i += 1;
		return (0);
	}
	list->command[list->number] = malloc(size + 1);
	if (!list->command[list->number])
		return (-1);
	ft_strlcpy(list->command[list->number], command->word + *i, size + 1);
	*i += size;
	list->number += 1;
	list->command[list->number] = NULL;
	return (0);
}

int	get_pipe(t_list_commands *list, int character)
{
	char	*temp;

	list->command[list->number] = malloc(2);
	temp = list->command[list->number];
	if (character == PIPE)
	{	
		if (!list->command[list->number])
			return (-1);
		list->command[list->number] = "|";
	}
	else if (character == SEMICOLON)
	{
		if (!list->command[list->number])
			return (-1);
		list->command[list->number] = ";";
	}
	list->number += 1;
	list->command[list->number] = NULL;
	free (temp);
	return (0);
}

t_list_commands	*start_parse(t_command *command, t_list_commands *list)
{
	size_t	i;
	int		ret;
	char	*temp;

	i = 0;
	while (i < command->len && command->word[i] != '\0')
	{
		list->type[list->number] = search_for_type(command, i);
		if (list->type[list->number] == BUILT_IN)
			ret = get_built_in_cmd(command, list, &i);
		else if (list->type[list->number] == PIPE
			|| list->type[list->number] == SEMICOLON)
		{
			ret = get_pipe(list, list->type[list->number]);
			i++;
		}
		else if (list->type[list->number] == SINGLE_QM
			|| list->type[list->number] == DOUBLE_QM)
		{
			ret = handle_quotes(list, command, list->type[list->number], &i);
			if (list->type[list->number - 1] == DOUBLE_QM)
				while (ft_strchr(list->command[list->number - 1], '$') >= 0)
				{
					if (ft_strchr(list->command[list->number - 1], '$')
						== (int)ft_strlen(list->command[list->number - 1]) - 1)
					{
						list->command[list->number] = ft_strdup("");
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
			i++;
		}
		else if (list->type[list->number] >= REDIRECT_RIGHT
			&& list->type[list->number] <= REDIRECT_AND_APPEND)
				ret = handle_redirects(list, list->type[list->number], &i);
		else if (list->type[list->number] == ENVIRONMENT_VAR)
		{
			get_built_in_cmd(command, list, &i);
			if (list->command[list->number - 1][0] != '\''
				&& list->command[list->number - 1][0] != '\"'
				&& ft_strlen(list->command[list->number - 1]) > 1)
			{
				temp = list->command[list->number - 1];
				list->command[list->number - 1]
					= get_env_var_value(
						list->env_vars, list->command[list->number - 1] + 1);
				// if (temp)
				//free (temp);
				// temp = list->command[list->number - 1];
				// list->command[list->number - 1]
				// 	= get_prefix_for_env(
				// 		list->env_vars, list->command[list->number - 1]);
				// free (temp);
			}
		}
		if (list->number == 1 && list->type[0] == ENVIRONMENT_VAR)
		{
			int	j;
			int	*temp2;
			char **split_string;
			//char	*temp4;
			char	**temp3;
			int		counter;

			j = 0;
			counter = 0;
			list->number = 0;
			while (list->command[0][j])
			{
				if (list->command[0][j] == ' ')
					counter++;
				j++;
			}
			j = 0;
			split_string = ft_split(list->command[0], ' ');
			temp2 = list->type;
			temp3 = list->command;
			//temp4 = list->command[0];
			list->command = malloc(sizeof(char *) * (command->len + 1) + sizeof(char *) * (counter * 2 + 1));
			list->type = malloc(sizeof(int *) * (command->len + 1) + sizeof(int *) * (counter * 2 + 1));
			if (!list->command || !list->type)
				return (NULL);
			while (split_string[j])
			{
				list->command[list->number] = ft_strdup(split_string[j]);
				//printf("inside %s\n", list->command[list->number]);
				list->type[list->number] = BUILT_IN;
				list->number += 1;
				list->command[list->number] = malloc(1);
				list->command[list->number][0] = '\0';
				list->type[list->number] = SEP_SPACE;
				list->number += 1;
				list->command[list->number] = NULL;
				j++;
			}
			//free (temp4);
			free (temp2);
			free (temp3);
			j = 0;
			while (split_string[j])
			{
				if (split_string[j])
					free (split_string[j]);
				j++;
			}
			free (split_string);
		}
		if (command->word[i] == ' ')
		{
			list->command[list->number] = malloc(1);
			list->command[list->number][0] = '\0';
			list->type[list->number] = SEP_SPACE;
			list->number += 1;
			list->command[list->number] = NULL;
		}
		else
			continue ;
		while (command->word[i] == ' ')
			i++;
	}
	if (ret < 0)
		return (NULL);
	return (list);
}