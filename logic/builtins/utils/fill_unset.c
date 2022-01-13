/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:56:10 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 17:59:36 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../logic/logic.h"

char	**fill_unset(char **old, int old_len, int final_len)
{
	char	**result;
	int		i;
	int		j;

	result = malloc(sizeof(char *) * (final_len + 1));
	if (!result)
	{
		malloc_error(result);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (++i <= old_len)
	{
		if (old[i])
		{
			result[j] = old[i];
			j++;
		}
	}
	result[j] = NULL;
	//printf("result[j] = %s\n", result[j]);
	free(old);
	old = NULL;
	return (result);
}
