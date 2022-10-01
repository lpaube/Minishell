#include "libft.h"
#include <stdlib.h>

void	ft_treeclear(t_btree **tree, void (*del)(void *))
{
	if (*tree)
	{
		if ((*tree)->left)
			ft_treeclear(&(*tree)->left, del);
		if ((*tree)->right)
			ft_treeclear(&(*tree)->right, del);
		del((*tree)->content);
		free(*tree);
		*tree = NULL;
	}
}
