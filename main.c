#include "../logic/logic.h"
//#include "../simple_parser/parser.h"

int	free_and_exit(t_command *command, t_list_commands *list, int ret)
{
	int	i;

	(void)command;
	i = -1;
	if (list->env_vars[++i])
	{
		while (list->env_vars[i++])
			free(list->env_vars[i]);
	}
	free (list->env_vars);
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

t_list_commands	*get_pipe_fd(t_list_commands *list, t_list_commands *temp)
{
	temp->p = list->p;
	temp->type = list->type;
	temp->pipe_left = list->pipe_left;
	temp->pipe_right = list->pipe_right;
	list->stdin_copy = STDIN_FILENO;
	list->stdout_copy = STDOUT_FILENO;
	temp->fd[0] = list->fd[0];
	temp->fd[1] = list->fd[1];
	temp->stdin_copy = list->stdin_copy;
	temp->stdout_copy = list->stdout_copy;
	temp->redirect = list->redirect;
	// if (list->pipe_right)
	// {
		list->pipe_right--;
		list->pipe_left++;
	//}
	if (list->pipe_right == 0)
		list->pipe_right = -1;
	return (list);
}

void	free_temp(t_list_commands *temp, int j)
{
	while (j)
	{
		free (temp->command[j]);
		j--;
	}
}

int	start_pipe(t_list_commands *list, char **envp)
{
	int					i;
	int					j;
	t_list_commands		*temp;

	i = 0;
	j = 0;
	temp = malloc(sizeof(t_list_commands));
	temp->command = malloc(sizeof(char *) * (list->p->len + 1));
	temp->type = malloc(sizeof(int *) * (list->p->len + 1));
	duplicate_envp(envp, temp);
	//get_pipe_fd(list, temp);
	if (!temp)
		return (0);
	while (list->command[i] && i < list->number)
	{
		while (list->command[i] && list->type[i] != PIPE && i < list->number)
		{
			temp->command[j] = ft_strdup(list->command[i]);
			temp->type[j] = list->type[i];
			if (list->type[i] >= REDIRECT_RIGHT
				&& list->type[i] <= REDIRECT_AND_APPEND)
				temp->redirect = 1;
			j++;
			i++;
		}
		if (list->command[i] != NULL && list->command[i][0] != '|') {
			temp->pipe_right = 0;
		}
		temp->number = j;
		while (j < list->number)
			temp->command[j++] = NULL;
		 //here is a double free error
		while (get_redirect_type(temp) > 0)
		{
			if (rid_of_redirect_right(temp) == -1)
			{
				g_error_code = 1;
				break ;
			}
		}
		// dup2(temp->fd[0], STDIN_FILENO);
		// dup2(temp->fd[1], STDOUT_FILENO);
		start_cmd(temp);
		i++;
		j = 0;
		// set_default_fd();
		if (temp->redirect)
		{
			set_default_fd();
			dup2(temp->fd[0], STDIN_FILENO);
			dup2(temp->fd[1], STDOUT_FILENO);
		}
		start_cmd(temp);
		i++;
		j = 0;
		temp->redirect = 0;
	}
	free (temp);
	return (0);
}

/*free and exit doesn't work, because no malloc*/
int	main(int argc, char **argv, char **envp)
{
	t_command		command;
	t_list_commands	list;
	char			*string;

	if (argc && argv)
		duplicate_envp(envp, &list);
	init_stdcopies_g_error(&list, &command);
	ft_s_h();
	// string = "VSCODE_GIT_ASKPASS_EXTRA_ARGS";
	// get_env_var_value(list.env_vars, string);
	while (1)
	{
		string = (readline("minishell$>"));
		if (!string)
			exit(0);//free_and_exit(&command, &list, -1);
		if (ft_strlen(string))
		{
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
				//print_commands_and_words(&list);
				// if (list.fd[0] != -1 && list.fd[1] != -1
				// 	&& ft_strlen(list.command[0]))
				get_normal_array(&list);
				//print_commands_and_words(&list);
				start_pipe(&list, envp);
			}
			else
			{
				g_error_code = 2;
				write(1, "bash: syntax error near unexpected token `newline'\n", 52);
			}
			//free (string);
			set_default_fd();
			//free_cmd(&list);
			printf("All good here2\n");
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
	}
		//print_commands_and_words(&list);
	//}
	//free_and_exit(&command, &list, 0);
	exit(0);
	//return (0);
}	
