#include "../simple_parser/parser.h"

/*search for first occurence of little string in big string,
return pointer to first occurence or NULL*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (big == little)
		return ((char *)big);
	if (!*little)
		return ((char *)big);
	// printf("big is %s\n", big);
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[j])
		{
			j++;
			if ((big[i + 1] != little[j] && little[j] != '\0'))
				j = 0;
			if (big[i - 1] == little[j] && little[j] != '\0')
				j++;
			if (little[j] == '\0')
				return ((char *)big + i - j + 1);
		}
		i++;
	}
	return (NULL);
}
