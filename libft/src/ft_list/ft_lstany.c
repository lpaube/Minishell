#include "libft.h"

bool	ft_lstany(t_list *lst, bool (*f)(void *))
{
	while (lst)
	{
		if (f(lst->content))
			return (true);
		lst = lst->next;
	}
	return (false);
}
