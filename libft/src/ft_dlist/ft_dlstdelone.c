#include "libft.h"
#include <stdlib.h>

void	ft_dlstdelone(t_dlist *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}
