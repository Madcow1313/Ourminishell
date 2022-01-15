/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_multiple_spaces.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaryett <jmaryett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 01:22:14 by jmaryett          #+#    #+#             */
/*   Updated: 2022/01/16 01:22:37 by jmaryett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

int	check_multiple_spaces(char **s)
{
	int	i;
	int	not_empty_s;
	int	j;

	not_empty_s = 0;
	i = 0;
	while (s[++i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] != ' ')
				not_empty_s = 1;
			j++;
		}
	}
	return (not_empty_s);
}
