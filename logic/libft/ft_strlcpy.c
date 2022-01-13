/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:35:05 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:35:05 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t		i;
	size_t		n;

	i = 0;
	if (!dst || !src)
		return (0);
	if (len > 0)
	{
		while (src[i] && --len)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	n = ft_strlen(src);
	return (n);
}
