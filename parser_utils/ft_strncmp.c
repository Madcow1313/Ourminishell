/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:17:56 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/16 01:17:56 by wabathur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../simple_parser/parser.h"

/*compare strings, returns int (0, >0, <0)*/
int	ft_strncmp(const char *string1, const char *string2, size_t num)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = 0;
	str1 = (const unsigned char *) string1;
	str2 = (const unsigned char *) string2;
	while (str1[i] == str2[i] && i < num && str1[i] != '\0')
		i++;
	if (i == num)
		return (0);
	else
		return (str1[i] - str2[i]);
}
