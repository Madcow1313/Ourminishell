/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 15:23:41 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/15 15:31:02 by wabathur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../logic/logic.h"

void	free_previous(t_list_commands *list)
{
	int	i;

	i = 0;
	while (i < list->number && list->command[i])
	{
		if (list->command[i])
			free (list->command[i]);
		i++;
	}
	free (list->command);
}

int	proc_red_and_space(
	t_list_commands *list, char **new, int *i, int *j)
{
	while (list->type[*i] == SEP_SPACE && *i < list->number)
		*i += 1;
	while ((list->type[*i] == SEP_SPACE || list->type[*i] == PIPE
			|| (list->type[*i] >= REDIRECT_RIGHT
				&& list->type[*i] < ENVIRONMENT_VAR))
		&& list->command[*i])
	{
		while (list->type[*i] == SEP_SPACE && *i < list->number)
			*i += 1;
		new[*j] = ft_strdup(list->command[*i]);
		if (!new[*j])
			return (0);
		list->type[*j] = list->type[*i];
		*i += 1;
		*j += 1;
	}
	return (1);
}

int	proc_else(
	t_list_commands *list, char **new, int *i, int *j)
{
	char	*temp;

	while (list->type[*i] != SEP_SPACE && list->type[*i] != PIPE
		&& ((list->type[*i] < REDIRECT_RIGHT
				|| list->type[*i] > REDIRECT_AND_APPEND))
		&& list->command[*i])
	{
		temp = new[*j];
		new[*j] = ft_strjoin(new[*j], list->command[*i]);
		if (!new[*j])
			return (0);
		if (i > 0)
			list->type[*j] = list->type[*i];
		free (temp);
		*i += 1;
	}
	return (1);
}

void	set_type(t_list_commands *list, char **new, int i, int j)
{
	list->type[j] = BUILT_IN;
	if (list->type[j - 1] >= REDIRECT_RIGHT
		&& list->type[j - 1] < ENVIRONMENT_VAR)
		list->type[j - 1] = BUILT_IN;
	if (list->type[j - 1] == SEP_SPACE)
		new[j - 1] = NULL;
	while (j < i)
	{
		new[j] = NULL;
		j++;
	}
}

/*no malloc protection, leaks*/
char	**get_normal_array(t_list_commands *list)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (list->number));
	if (!new)
		return (list->command);
	while (list->command[i] && i < list->number)
	{
		if (!proc_red_and_space(list, new, &i, &j))
			break ;
		new[j] = malloc(1);
		if (!new[j])
			return (list->command);
		new[j][0] = '\0';
		if (!proc_else(list, new, &i, &j))
			break ;
		j++;
	}
	set_type(list, new, i, j);
	free_previous(list);
	list->command = new;
	return (list->command);
}
