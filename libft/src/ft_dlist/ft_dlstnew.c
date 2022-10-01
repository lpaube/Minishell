#include "libft.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*node;

	node = ft_calloc(1, sizeof(t_dlist));
	if (!node)
		return (NULL);
	node->content = content;
	return (node);
}
