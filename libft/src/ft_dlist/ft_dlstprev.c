#include "libft.h"

t_dlist	*ft_dlstprev(t_dlist **lst)
{
	if (*lst)
	{
		*lst = (*lst)->prev;
		return (*lst);
	}
	return (NULL);
}
