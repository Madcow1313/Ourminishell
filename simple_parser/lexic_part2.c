#include "parser.h"

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
			return (READ_INPUT);
		return (REDIRECT_LEFT);
	}
}

int	search_for_type(t_command *command, int i)
{
	if (ft_strchr("><$\'\"|;", command->word[i]) >= 0)
	{
		if (command->word[i] == '\'')
			return (SINGLE_QM);
		if (command->word[i] == '\"')
			return (DOUBLE_QM);
		if (command->word[i] == '>' || command->word[i] == '<')
			return (define_redirect(command, i));
		if (command->word[i] == '$')
			return (ENVIRONMENT_VAR);
		if (command->word[i] == ';')
			return (SEMICOLON);
		if (command->word[i] == '|')
			return (PIPE);
	}
	else
		return (BUILT_IN);
	return (BUILT_IN);
}

int get_built_in_cmd(t_command *command, t_list_commands *list, size_t *i)
{
	size_t size;

	size = 0;
	while (command->word[*i + size] != ' ' && command->word[*i + size] != '\0'
		&& command->word[*i + size] != ';' && size <= command->len - *i)
	{
		size++;
	}
	list->command[list->number] = malloc(size + 1);
	if (!list->command[list->number])
		return(-1);
	ft_strlcpy(list->command[list->number], command->word + *i, size + 1);
	*i += size;
	list->number += 1;
	list->command[list->number] = NULL;
	return (0);
}

int	get_pipe(t_list_commands *list, int	character)
{
	if (character == PIPE)
	{	
		list->command[list->number] = malloc(5);
		if (!list->command[list->number])
			return (-1);
		list->command[list->number] = "pipe";
	}
	else if (character == ENVIRONMENT_VAR)
	{
		list->command[list->number] = malloc(4);
		if (!list->command[list->number])
			return (-1);
		list->command[list->number] = "var";
	}
	else if (character == SEMICOLON)
	{
		list->command[list->number] = malloc(11);
		if (!list->command[list->number])
			return (-1);
		list->command[list->number] = "semicolon";
	}
	list->number += 1;
	list->command[list->number] = NULL;
	return (0);
}

t_list_commands	*start_parse(t_command *command, t_list_commands *list)
{
	size_t	i;

	i = 0;
	while (i < command->len && command->word[i] != '\0')
	{
		list->type[list->number] = search_for_type(command, i);
		if (list->type[list->number] == BUILT_IN)
		{
			if (get_built_in_cmd(command, list, &i) == -1)
				return (NULL);
		}
		else if (list->type[list->number] == PIPE
		|| list->type[list->number] == ENVIRONMENT_VAR
		|| list->type[list->number] == SEMICOLON)
		{
			if (get_pipe(list, list->type[list->number]) == -1)
				return (NULL);
			i++;
		}
		else if (list->type[list->number] == SINGLE_QM
				|| list->type[list->number] == DOUBLE_QM)
		{
			if (handle_quotes(list, command, list->type[list->number], &i) == -1)
				return (NULL);
			i++;
		}
		if (command->word[i] == ' ')
			i++;
	}
	return (list);
}