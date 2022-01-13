/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:34:56 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:34:56 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	index;
	int				comp_value;

	index = 0;
	if (!s1 || !s2)
		return (s1 == s2);
	while (s1[index] || s2[index])
	{
		comp_value = (unsigned char)s1[index] - (unsigned char)s2[index];
		if (comp_value)
			return (comp_value);
		index++;
	}
	return (0);
}
