#include "./simple_parser/parser.h"

int	free_and_exit(t_command *command, t_list_commands *list, int ret)
{
	if (command)
		free (command);
	if (list->type)
		free (list->type);
	if (list->command)
	{
		while (list->number > 0)
		{
			if (list->command[list->number])
				free (list->command[list->number]);
			list->number--;
		}
		free (list->command);
	}
	if (list)
		free (list);
	return (ret);
}

int	main()
{
	t_command	command;
	t_list_commands list;
	const char *string;

	while (1)
	{
		printf("I am waiting for your command, my lord!\n");
		string = (readline(""));
		if (!string)
			free_and_exit(&command, &list, -1);
		get_full_command(string, &command);
		if (prepare_list(&list, &command) == -1)
			return (free_and_exit(&command, &list, -1));
		if (start_parse(&command, &list) == NULL)
			return (free_and_exit(&command, &list, -1));
		print_commands_and_words(&list);
	}
	free_and_exit(&command, &list, 0);
	return (0);
}