#include "libft.h"

t_btree	*ft_treenew(void *content)
{
	t_btree	*node;

	node = ft_calloc(1, sizeof(t_btree));
	if (!node)
		return (NULL);
	node->content = content;
	return (node);
}
