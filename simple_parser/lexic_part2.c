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
	if (ft_strchr_parser("><$\'\"|;./", command->word[i]) >= 0)
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
			return (BUILT_IN);
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
		&& command->word[*i + size] != '>' && command->word[*i + size] != '<'
		&& command->word[*i + size] != '\"' && command->word[*i + size] != '\''
		&& command->word[*i + size] != '|')
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
		return (0);
	ft_strlcpy(list->command[list->number], command->word + *i, size + 1);
	*i += size;
	list->number += 1;
	list->command[list->number] = NULL;
	return (1);
}

int	get_pipe(t_list_commands *list, int character)
{
	char	*temp;

	list->command[list->number] = malloc(2);
	if (!list->command[list->number])
		return (0);
	temp = list->command[list->number];
	if (character == PIPE)
	{	
		if (!list->command[list->number])
			return (-1);
		list->command[list->number] = ft_strdup("|");
		if (!list->command[list->number])
			return (0);
		if (list->pipe_right == -1)
		{
			list->pipe_right = 0;
			list->pipe_left = 0;
		}
		list->pipe_right += 1;
	}
	list->number += 1;
	list->command[list->number] = NULL;
	free (temp);
	return (1);
}
