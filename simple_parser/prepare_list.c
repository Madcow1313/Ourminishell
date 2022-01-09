#include "parser.h"

int	prepare_list(t_list_commands *list, t_command *command)
{
	// if (list->command)
	// 	free (list->command);
	list->command = malloc(sizeof(list->command) * (command->len));
	// if (list->type)
	// 	free (list->type);
	list->type = malloc(sizeof(list->type) * (command->len));
	list->fd[0] = 0;
	list->fd[1] = 1;
	if (!list->command || !list->type)
	{
		if (list->command)
			free (list->command);
		if (list->type)
			free (list->type);
		return (-1);
	}
	list->number = 0;
	return (0);
}
