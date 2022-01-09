#include "parser.h"

/*no malloc protection, leaks*/
char	**get_normal_array(t_list_commands *list)
{
	char	**new;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * list->number);
	while (list->command[i] && i < list->number)
	{
		while (list->type[i] == SEP_SPACE && i < list->number)
				i++;
		new[j] = malloc(1);
		new[j][0] = '\0';
		while ((list->type[i] == SEP_SPACE || (list->type[i] >= REDIRECT_RIGHT && list->type[i] < ENVIRONMENT_VAR))
			&& list->command[i])
		{
			while (list->type[i] == SEP_SPACE && i < list->number)
				i++;
			temp = new[j];
			new[j] = ft_strjoin(new[j], list->command[i]);
			list->type[j] = list->type[i];
			free(temp);
			i++;
			j++;
			new[j] = malloc(1);
			new[j][0] = '\0';
		}
		while(list->type[i] != SEP_SPACE && ((list->type[i] < REDIRECT_RIGHT || list->type[i] > REDIRECT_AND_APPEND))
			&& list->command[i] && i < list->number)
		{
			temp = new[j];
			new[j] = ft_strjoin(new[j], list->command[i]);
			if (i > 0)
				list->type[j] = list->type[i];
			free (temp);
			i++;
		}
		j++;
	}
	list->type[j - 1] = BUILT_IN;
	new[j] = NULL;
	i = 0;
	// while (i < list->number && list->command[i])
	// {
	// 	if (list->command[i])
	// 		free (list->command[i]);
	// 	i++;
	// }
	free (list->command);
	list->command = new;
	return (list->command);
}