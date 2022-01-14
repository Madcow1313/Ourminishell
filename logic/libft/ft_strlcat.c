/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:35:02 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:35:02 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstlen;

	i = 0;
	dstlen = ft_strlen(dst);
	if (size < dstlen)
		return (ft_strlen(src) + size);
	if (size > 0)
	{
		while (src[i] && dstlen + 1 < size)
		{
			dst[dstlen++] = src[i];
			i++;
		}
		dst[dstlen] = '\0';
	}
	while (src[i])
	{
		i++;
		dstlen++;
	}
	return (dstlen);
}
