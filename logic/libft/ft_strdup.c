#include "libft.h"

char	*ft_strdup(const char *str)
{
	unsigned int	i;
	char			*copy;

	i = 0;
	if (!str)
		return (NULL);
	copy = (char *)malloc(sizeof(*copy) * ft_strlen(str) + 1);
	if (!copy)
		return (NULL);
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
