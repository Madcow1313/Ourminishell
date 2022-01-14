/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:34:50 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:34:50 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**free_array(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		free (t[i]);
		i++;
	}
	free(t);
	t = NULL;
	return (t);
}

static	char	**filling_strings(char const *s, char c, char **t, size_t j)
{
	size_t	i;
	size_t	k;
	size_t	l;

	i = 0;
	k = 0;
	while (k < j && s[i])
	{
		if (s[i] != c)
		{
			l = 0;
			while (s[i] != c && s[i])
			{
				t[k][l] = s[i];
				l++;
				i++;
			}
			t[k][l] = '\0';
			k++;
		}
		i++;
	}
	return (t);
}

static	char	**mem_for_arrays(char const *s, char c, char **t, size_t j)
{
	size_t	k;
	size_t	l;
	size_t	i;

	k = 0;
	i = -1;
	while (k < j && s[++i])
	{
		l = 0;
		while (s[i] != c && s[i])
		{
			l++;
			i++;
		}
		if (l != 0)
		{
			t[k++] = malloc(sizeof(char) * (l + 1));
			if (!t)
			{
				t = free_array(t);
				return (t);
			}
		}
	}
	return (t);
}

static	int	count_first_array(const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	s_len;

	i = 0;
	j = 0;
	s_len = ft_strlen(s);
	while ((s[i] == c) && s[i])
		i++;
	if (i == s_len)
		return (0);
	while (s[++i])
	{
		if ((s[i] != c) && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	size_t	j;
	char	**t;

	if (!s)
		return (NULL);
	j = count_first_array(s, c);
	t = malloc(sizeof(char *) * (j + 1));
	if (!t)
		return (NULL);
	t[j] = NULL;
	t = mem_for_arrays(s, c, t, j);
	t = filling_strings(s, c, t, j);
	return (t);
}
