#include "libft.h"
#include <stdlib.h>

void	ft_treedelone(t_btree *tree, void (*del)(void *))
{
	if (tree)
	{
		del(tree->content);
		free(tree);
	}
}
