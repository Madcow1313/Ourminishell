/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chudapak <chudapak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:33:46 by chudapak          #+#    #+#             */
/*   Updated: 2022/01/13 18:33:46 by chudapak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	void	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->content;
		f(tmp);
		lst = lst->next;
	}
}
