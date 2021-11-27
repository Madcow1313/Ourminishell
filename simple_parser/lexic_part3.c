#include "parser.h"

int	handle_quotes(t_list_commands *list, t_command *command, int character, size_t *i)
{
	size_t	count;
	size_t	start;
	size_t	k;

	count = 0;
	*i += 1;
	start = *i;
	k = 0;
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