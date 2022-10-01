#include "libft.h"

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*last;

	if (*lst)
	{
		last = ft_dlstlast(*lst);
		last->next = new;
		if (new)
			new->prev = last;
	}
	else
		*lst = new;
}
