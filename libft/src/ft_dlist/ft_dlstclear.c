#include "libft.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_dlstdelone(*lst, del);
		*lst = tmp;
	}
}
