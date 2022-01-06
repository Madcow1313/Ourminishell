#include "../logic/logic.h"

int	check_first_symbol(char c)
{
	if ((c >= 33 && c <= 64) || (c >= 91 && c <= 96)
		|| (c >= 123 && c <= 126))
		return (0);
	return (1);
}

int	wrong_symbols(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '`' || str[i] == '\\' || str[i] == '(' || str[i] == ')'
			|| str[i] == '&' || str[i] == '<' || str[i] == '>' || str[i] == '|')
			return (0);
		i++;
	}
	return (1);
}