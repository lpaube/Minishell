#include "libft.h"

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	t_dlist	*first;

	if (*lst && new)
	{
		first = ft_dlstfirst(*lst);
		new->next = first;
		new->prev = NULL;
		first->prev = new;
	}
	*lst = new;
}
