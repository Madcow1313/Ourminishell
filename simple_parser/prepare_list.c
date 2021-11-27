#include "parser.h"

int	prepare_list(t_list_commands *list, t_command *command)
{
	list->command = malloc(sizeof(list->command) * (command->len));
	list->type = malloc(sizeof(list->type) * (command->len));
	if (!list->command || !list->type)
	{
		if(list->command)
			free (list->command);
		if (list->type)
			free (list->type);
		return (-1);
	}
	list->command[0] = NULL;
	list->number = 0;
	return (0);
}
