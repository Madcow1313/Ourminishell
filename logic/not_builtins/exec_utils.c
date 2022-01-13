/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:42:21 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:42:21 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

/*compare strings, returns int (0, >0, <0)*/

int	ft_cmprcmd(const char *string1, const char *string2)
{
	size_t				i;
	size_t				len1;
	size_t				len2;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = 0;
	str1 = (const unsigned char *) string1;
	str2 = (const unsigned char *) string2;
	len1 = ft_strlen((const char *)str1);
	len2 = ft_strlen((const char *)str2);
	if (len1 != len2)
		return (-1);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}
