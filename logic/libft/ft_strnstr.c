#include "libft.h"

char	*ft_strnstr(const char *haystak, const char *needle, size_t len)
{
	char	*s1;
	char	*s2;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	s1 = (char *)haystak;
	s2 = (char *)needle;
	if (*needle == '\0')
		return (s1);
	while (s1[i] && i < len)
	{
		j = 0;
		while (s2[j] == s1[i + j] && i + j < len)
		{
			if (s2[j + 1] == '\0')
				return (&s1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
