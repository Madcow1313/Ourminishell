#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	*s;
	size_t	i;

	s = (char *)str;
	i = ft_strlen(str);
	if ((char)ch == '\0')
		return (s + i);
	while (i--)
	{
		if (s[i] == (char)ch)
			return (s + i);
	}
	return (NULL);
}
