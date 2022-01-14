#include "../logic/logic.h"
//#include "../simple_parser/parser.h"

int	free_and_exit(t_command *command, t_list_commands *list, int ret)
{
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

int	check_redirects(t_list_commands *list)
{
	int	i;

	i = 0;
	if (get_redirect_type(list))
	{
		while (list->command[i] && i < list->number - 1)
			i++;
		if (list->type[i] >= REDIRECT_RIGHT
			&& list->type[i] <= REDIRECT_AND_APPEND)
			return (1);
		if (list->type[i - 1] >= REDIRECT_RIGHT
			&& list->type[i - 1] <= REDIRECT_AND_APPEND
			&& list->command[i] && !ft_strlen(list->command[i]))
			return (1);
		else 
			return (0);
	}
	return (0);
}

int	start_pipe(t_list_commands *list, t_command *command)
{
	int	i;
	int j;
	t_list_commands *temp;
	
	i = 0;
	j = 0;
	temp = malloc(sizeof(list));
	temp->type = list->type;
	//temp->fd = list.fd;
	temp->pipe_left = list->pipe_left;
	temp->pipe_right = list->pipe_right;
	temp->command = malloc(sizeof(char *) * list->number);
	if (!temp)
		return (0);
	while (list->command[i] && i < list->number)
	{
		while (list->command[i] && list->type[i] != PIPE && i < list->number)
		{
			//printf("%s\n", list->command[i]);
			temp->command[j] = ft_strdup(list->command[i]);
			//write(1, "here0.35\n", 9);
			//printf("** %s\n", temp->command[j]);
			j++;
			i++;
		}
		//write(1, "here0.5\n", 8);
		temp->fd[0] = list->fd[0];
		temp->fd[1] = list->fd[1];
		temp->command[j] = NULL;
		print_commands_and_words(temp);
		//write(1, "here1\n", 6);
		start_cmd(temp, command);
		write(1, "here2\n", 6);
		if (list->pipe_right)
		{
			list->pipe_right--;
			list->pipe_left++;
		}
		i++;
		// while (j)
		// {
		// 	free (temp->command[j]);
		// 	j--;
		// }
		j = 0;
	}
	//free (temp);
	return (0);
}


/*free and exit doesn't work, because no malloc*/
int	main(int argc, char **argv, char **envp)
{
	t_command	command;
	t_list_commands list;
	const char 	*string;

	if (argc && argv)
		duplicate_envp(envp, &list);
	init_stdcopies_g_error(&list);
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
			exit (0);
		if (start_parse(&command, &list) == NULL)
			exit (0);
		if (!delete_quotes(&list))
			exit(EXIT_FAILURE);
		//print_commands_and_words(&list);
		if (!check_redirects(&list))
		{
			//print_commands_and_words(&list);
			get_normal_array(&list); //here is a double free error
			while (get_redirect_type(&list) > 0)
				rid_of_redirect_right(&list);
			//print_commands_and_words(&list);
			if (list.pipe_right != -1)
			{
				start_pipe(&list, &command);
			}
			else
				start_cmd(&list, &command);
		}
		else
		{
			g_error_code = 2;
			write(1, "bash: syntax error near unexpected token `newline'\n", 52);
		}
		set_default_fd(&list);
		// int	i = 0;
		// while (i < list.number && list.command[i])
		// {
		// 	if (list.command[i])
		// 		free (list.command[i]);
		// 	i++;
		// }
		// free (list.command);
		// free (list.type);
	}
		//print_commands_and_words(&list);
	//}
	//free_and_exit(&command, &list, 0);
	exit(0);
	//return (0);
}	
