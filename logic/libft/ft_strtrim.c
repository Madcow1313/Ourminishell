#include "libft.h"

static	int	ft_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	char		*copy;
	size_t		i;
	size_t		j;
	size_t		k;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = 0;
	k = ft_strlen(s1);
	while (s1[i] && ft_set(s1[i], set))
		i++;
	while (k > i && ft_set(s1[k - 1], set))
		k--;
	copy = (char *)malloc(sizeof(char) * (k - i + 1));
	if (!copy)
		return (NULL);
	while (i < k)
		copy[j++] = s1[i++];
	copy[j] = '\0';
	return (copy);
}
