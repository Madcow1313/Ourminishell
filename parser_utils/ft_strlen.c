/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:17:53 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/16 01:18:38 by wabathur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../simple_parser/parser.h"

size_t	ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i] != '\0')
	{
		i++;
	}
	return (i);
}
