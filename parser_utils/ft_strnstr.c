/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:17:59 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/16 01:17:59 by wabathur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../simple_parser/parser.h"

/*search for first occurence of little string in big string,
return pointer to first occurence or NULL*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (big == little)
		return ((char *)big);
	if (!*little)
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[j])
		{
			j++;
			if ((big[i + 1] != little[j] && little[j] != '\0'))
				j = 0;
			if (big[i - 1] == little[j] && little[j] != '\0')
				j++;
			if (little[j] == '\0')
				return ((char *)big + i - j + 1);
		}
		i++;
	}
	return (NULL);
}
