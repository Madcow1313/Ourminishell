#include "parser.h"

void	print_commands_and_words(t_list_commands *list)
{
	int	i;

	i = 0;
	while (list->command[i] != NULL && i < list->number)
	{
		printf("%s %d\n", list->command[i], list->type[i]);
		i++;
	}
}
