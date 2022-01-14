/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabathur <wabathur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:23:36 by wabathur          #+#    #+#             */
/*   Updated: 2022/01/14 16:23:42 by wabathur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../simple_parser/parser.h"

/*search for first occurence of symbol in string*/
int	ft_strchr_parser(const char *string, int symbol)
{
	int	i;

	i = 0;
	symbol = (char ) symbol;
	if (symbol == '\0')
	{
		while (*(string) != '\0')
			i++;
		return (i);
	}
	while (*string != symbol && *string != '\0')
	{
		string++;
		i++;
	}
	if (*string == '\0')
		return (-1);
	return (i);
}

int	ft_strchr_for_dq(const char *string, int symbol)
{
	int	i;

	i = 0;
	symbol = (char ) symbol;
	while (string[i] != '\0')
	{
		if (string[i] == symbol && string[i + 1] != ' '
			&& string[i + 1] != '\0')
		{
			break ;
		}	
		i++;
	}
	if (string[i] == '\0' || (int)ft_strlen(string) == i)
		return (-1);
	return (i);
}
