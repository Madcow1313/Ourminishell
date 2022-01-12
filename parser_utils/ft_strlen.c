#include "../simple_parser/parser.h"

size_t ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i] != '\0')
	{
		i++;
	}
	return (i);
}