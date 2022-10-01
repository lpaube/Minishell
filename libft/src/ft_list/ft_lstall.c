#include "libft.h"

bool	ft_lstall(t_list *lst, bool (*f)(void *))
{
	while (lst)
	{
		if (!f(lst->content))
			return (false);
		lst = lst->next;
	}
	return (true);
}
