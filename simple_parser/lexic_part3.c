#include "parser.h"

/*can't handle slash '\' */
int	handle_quotes(t_list_commands *list, t_command *command, int character, size_t *i)
{
	size_t	count;
	size_t	start;

	count = 0;
	*i += 1;
	start = *i;
	if (character == SINGLE_QM)
	{
		while (command->word[*i] != '\'' && command->word[*i] != '\0')
		{
			*i += 1;
			count++;
		}
	}
	else
	{
		while (command->word[*i] != '\"' && command->word[*i] != '\0')
		{
			*i += 1;
			count++;
		}
	}
	list->command[list->number] = malloc(count + 1);
	ft_strlcpy(list->command[list->number], command->word + start, count + 1);
	list->number += 1;
	list->command[list->number] = NULL;
	list->type[list->number] = WORD;
	return (0);
}

int	handle_redirects(t_list_commands *list, int character, size_t *i)
{
	list->command[list->number] = malloc(4);
	if (!list->command[list->number])
		return (-1);
	if (character == REDIRECT_RIGHT)
		list->command[list->number] = ">";
	else if (character == REDIRECT_LEFT)
		list->command[list->number] = "<";
	else if (character == REDIRECT_AND_APPEND)
		list->command[list->number] = ">>";
	else if (character == HERE_DOC)
		list->command[list->number] = "<<";
	*i += ft_strlen(list->command[list->number]);
	list->number += 1;
	list->command[list->number] = NULL;
	return (0);
}

int	handle_relative_path(t_list_commands *list, t_command *command, size_t *i)
{
	size_t	size;

	size = 0;
	while (ft_strchr("><$\"\'|", command->word[*i]) < 0 && *i < command->len
		&& command->word[*i] != '\0' && command->word[*i + size] != ' ')
	{
		size++;
		*i += 1;
	}
	list->command[list->number] = malloc(size + 1);
	if (!list->command[list->number])
		return (-1);
	ft_strlcpy(list->command[list->number],
		command->word + *i - size, size + 1);
	list->type[list->number] = RELATIVE_PATH;
	list->number += 1;
	list->command[list->number] = NULL;
	return (0);
}

int	handle_absolute_path(t_list_commands *list, t_command *command, size_t *i)
{
	size_t	size;

	size = 0;
	while (ft_strchr("><$\"\'|\n", command->word[*i + size]) < 0
		&& *i + size < command->len
		&& command->word[*i + size] != '\0'
		&& command->word[*i + size] != ' ')
		size++;
	list->command[list->number] = malloc(size + 1);
	if (!list->command[list->number])
		return (-1);
	ft_strlcpy(list->command[list->number], command->word + *i, size + 1);
	list->number += 1;
	list->command[list->number] = NULL;
	*i += size;
	return (0);
}
