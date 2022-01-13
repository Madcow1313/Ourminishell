/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:35:25 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:35:25 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
