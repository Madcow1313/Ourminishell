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
