#include "parser.h"

// static void		putchar_putstr(char *string)
// {
// 	int	i;

// 	i = 0;
// 	while (string[i])
// 	{
// 		write(1, &string[i], 1);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// }


void	print_commands_and_words(t_list_commands *list)
{
	int	i;

	i = 0;
	while (list->command[i] != NULL)
	{
		printf("%s %d\n", list->command[i], list->type[i]);
		//putchar_putstr(list->command[i]);
		i++;
	}
}
