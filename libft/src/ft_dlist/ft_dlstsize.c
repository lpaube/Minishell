#include "libft.h"

size_t	ft_dlstsize(t_dlist *lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		++size;
	}
	return (size);
}
