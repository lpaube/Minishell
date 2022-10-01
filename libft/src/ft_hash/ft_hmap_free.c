#include "libft.h"
#include "ft_hmap.h"
#include <stdlib.h>

void	ft_hmap_free(t_hmap map)
{
	t_hmap_	*m;
	size_t	i;
	t_list	*lst;
	t_list	*tmp;

	m = map;
	i = 0;
	while (i < m->size)
	{
		lst = m->data[i];
		while (lst)
		{
			tmp = lst->next;
			delete_pair(lst->content, m->del);
			free(lst);
			lst = tmp;
		}
		++i;
	}
	free(m->data);
	free(m);
}
