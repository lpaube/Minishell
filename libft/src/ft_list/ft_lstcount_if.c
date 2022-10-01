#include "libft.h"

size_t	ft_lstcount_if(t_list *lst, bool (*f)(void *))
{
	size_t	count;

	count = 0;
	while (lst)
	{
		if (f(lst->content))
			++count;
		ft_lstnext(&lst);
	}
	return (count);
}
