#include "../simple_parser/parser.h"

/*search for first occurence of symbol in string*/
int	ft_strchr(const char *string, int symbol)
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
