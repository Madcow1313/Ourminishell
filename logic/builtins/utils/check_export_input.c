#include "../logic/logic.h"

int	check_only_space(char *s)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while(s[++i])
	{
		if (s[i] != ' ')
			count = 1;
	}
	if (count == 1)
		return (1);
	return (0);
}

int	check_first_symbol(char c)
{
	if (c == '=' || (c >= 33 && c <= 64) || (c >= 91 && c <= 96)
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
			|| str[i] == '&' || str[i] == '|')
			return (0);
		i++;
	}
	return (1);
}