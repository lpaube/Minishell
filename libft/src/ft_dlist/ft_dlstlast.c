#include "libft.h"

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}
