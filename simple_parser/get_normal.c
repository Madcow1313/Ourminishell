#include "parser.h"

/*no malloc protection, leaks*/
char	**get_normal_array(t_list_commands *list)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(list->command));
	while (list->command[i] && i < list->number)
	{
		while (list->type[i] == SEP_SPACE || ((list->type[i] >= REDIRECT_RIGHT || list->type[i] < ENVIRONMENT_VAR)
			&& list->command[i]))
		{
			new[j] = malloc(2);
			new[j] = "";
			new[j] = ft_strjoin(new[j], list->command[i]);
			i++;
			j++;
		}
		new[j] = malloc(2);
		new[j] = "";
		while(list->type[i] != SEP_SPACE && ((list->type[i] < REDIRECT_RIGHT || list->type[i] > REDIRECT_AND_APPEND))
			&& list->command[i] && i < list->number)
		{
			//printf("here %s\n", list->command[i]);
			new[j] = ft_strjoin(new[j], list->command[i]);
			//printf("string in new array %d %d %s\n", j, i, list->command[i]);
			if (i > 0)
				list->type[j] = list->type[i];
			i++;
		}
		j++;
		i++;
	}
	new[j] = NULL;
	list->command = new;
	printf("hre %s\n", list->command[0]);
	return (list->command);
}