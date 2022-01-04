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
		if ((str[i] >= 33 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 64)
			|| (str[i] >= 91 && str[i] <= 96) || (str[i] >= 123 && str[i] <= 126))
			return (0);
		i++;
	}
	return (1);
}