#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*tmp;
	t_list	*new;
	t_list	*elem;

	if (!lst || !f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		tmp = lst->content;
		elem = ft_lstnew((*f)(tmp));
		if (!elem)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, elem);
		lst = lst->next;
	}
	return (new);
}
