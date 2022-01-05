#include "../logic/logic.h"
//#include "../simple_parser/parser.h"

int	free_and_exit(t_command *command, t_list_commands *list, int ret)
{
	// free (command);
	// if (list->type)
	// 	free (list->type);	if (command)
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
	(void)command;
	int	i;

	i = -1;
	if (list->env_vars[++i])
	{
		while (list->env_vars[i++])
			free(list->env_vars);
	}
	if (list->type)
		free(list->type);
	i = 0;
	while (i++ < 2)
		close(list->fd[i]);
	return (ret);
}

void	duplicate_envp(char **envp, t_list_commands *list)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	list->env_vars = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		list->env_vars[i] = ft_strdup(envp[i]);
		i++;
	}
	list->env_vars[i] = NULL;
}

/*free and exit doesn't work, because no malloc*/
int	main(int argc, char **argv, char **envp)
{
	t_command	command;
	t_list_commands list;
	const char 	*string;

	/*should be a copy, for now is fine*/
	if (argc && argv)
		duplicate_envp(envp, &list);
	ft_s_h();
	// string = "VSCODE_GIT_ASKPASS_EXTRA_ARGS";
	// get_env_var_value(list.env_vars, string);
	while (1)
	{
		string = (readline("minishell$>"));
		if (!string)
			exit(0);//free_and_exit(&command, &list, -1);
		add_history(string);
		get_full_command(string, &command);
		if (prepare_list(&list, &command) == -1)
			return (free_and_exit(&command, &list, -1));
		if (start_parse(&command, &list) == NULL)
			return (free_and_exit(&command, &list, -1));
		if (!delete_quotes(&list))
			exit(EXIT_FAILURE);
		//print_commands_and_words(&list);
		get_normal_array(&list);
		//print_commands_and_words(&list);
		while (get_redirect_type(&list))
			rid_of_redirect_right(&list);
		//list.command = get_no_space(&list);
		start_cmd(&list, &command);
		set_default_fd(&list);
	}
		//print_commands_and_words(&list);
	//}
	//free_and_exit(&command, &list, 0);
	exit(0);
	//return (0);
}
