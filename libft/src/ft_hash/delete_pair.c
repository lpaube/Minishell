#include "ft_hmap.h"
#include <stdlib.h>

void	delete_pair(void *pair, void (*del)(void *))
{
	t_pair	*p;

	p = pair;
	del(p->value);
	free(p->key);
	free(p);
}
