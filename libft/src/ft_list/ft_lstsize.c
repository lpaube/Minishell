#include "libft.h"

size_t	ft_lstsize(t_list *lst)
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
