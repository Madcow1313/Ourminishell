#include "parser.h"

int	prepare_list(t_list_commands *list, t_command *command)
{
	// if (list->command)
	// 	free (list->command);
	list->command = malloc(sizeof(char *) * (command->len + 1));
	// if (list->type)
	// 	free (list->type);
	list->type = malloc(sizeof(int *) * (command->len + 1));
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
	list->redirect = 0;
	list->pipe_right = 0;
	list->pipe_left = 0;
	list->number = 0;
	return (0);
}
