#include "parser.h"

char **get_no_space(t_list_commands *list)
{
	char **new_commands;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new_commands = malloc(sizeof(list->command));
	new_commands[0] = list->command[0];
	while (list->command[i])
	{
		i++;
		if (list->type[i] != SEP_SPACE)
		{
			ft_strjoin(new_commands[j], list->command[i]);
			list->type[j] = list->type[i];
			i++;
		}
		else
		{
			j++;
			i++;
			list->type[j] = list->type[i];
			new_commands[j] = new_commands[i];
		}
	}
	return (new_commands);
}
