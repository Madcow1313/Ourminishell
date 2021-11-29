#include "parser.h"

int	handle_quotes(t_list_commands *list, t_command *command, int character, size_t *i)
{
	size_t	count;
	size_t	start;
	//size_t	k;

	count = 0;
	*i += 1;
	start = *i;
	//k = 0;
	if (character == SINGLE_QM)
	{
		while (command->word[*i] != '\'')
		{
			*i += 1;
			count++;
		}
	}
	else
	{
		while (command->word[*i] != '\"')
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
	else if (character == READ_INPUT)
		list->command[list->number] = "<<";
	*i += ft_strlen(list->command[list->number]) + 1;
	list->number += 1;
	return (0);
}