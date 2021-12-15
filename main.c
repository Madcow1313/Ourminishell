#include "./simple_parser/parser.h"

int	free_and_exit(t_command *command, t_list_commands *list, int ret)
{
	if (command)
		free (command);
	if (list->type)
		free (list->type);
	// if (list->command)
	// {
	// 	while (list->number > 0)
	// 	{
	// 		if (list->command[list->number])
	// 			free (list->command[list->number]);
	// 		list->number--;
	// 	}
	// 	free (list->command);
	// }
	return (ret);
}

/*free and exit doesn't work, because no malloc*/
int	main(int argc, char **argv, char **envp)
{
	t_command	command;
	t_list_commands list;
	const char 	*string;

	/*should be a copy, for now is fine*/
	if (argc && argv)
		list.env_vars = envp;
	// string = "VSCODE_GIT_ASKPASS_EXTRA_ARGS";
	// get_env_var_value(list.env_vars, string);
	// while (1)
	// {
		string = (readline("I am waiting for your command, my lord!\n"));
		if (!string)
			free_and_exit(&command, &list, -1);
		get_full_command(string, &command);
		if (prepare_list(&list, &command) == -1)
			return (free_and_exit(&command, &list, -1));
		if (start_parse(&command, &list) == NULL)
			return (free_and_exit(&command, &list, -1));
		if (!delete_quotes(&list))
			exit(EXIT_FAILURE);
		get_normal_array(&list);
		while (get_redirect_type(&list)){
			rid_of_redirect_right(&list);
		}
		print_commands_and_words(&list);
	//}
	//free_and_exit(&command, &list, 0);
	//exit(0);
	return (0);
}
