#include "../simple_parser/parser.h"

/*search for first occurence of symbol in string*/
int	ft_strchr_parser(const char *string, int symbol)
{
	int i;

	i = 0;
	symbol = (char ) symbol;
	if (symbol == '\0')
	{
		while (*(string) != '\0')
			i++;
		return (i);
	}
	while (*string != symbol && *string != '\0')
	{
		string++;
		i++;
	}
	if (*string == '\0')
		return (-1);
	return (i);
}

int	ft_strchr_for_dq(const char *string, int symbol)
{
	int i;

	i = 0;
	symbol = (char ) symbol;
	while (string[i] != '\0')
	{
		if (string[i] == symbol && string[i + 1] != ' ')
		{
			write(1, "here\n", 5);
			break;
		}	
		i++;
	}
	if (string[i] == '\0')
		return (-1);
	return (i);
}
