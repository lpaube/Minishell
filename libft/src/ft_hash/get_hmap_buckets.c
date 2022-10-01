#include "libft.h"
#include "ft_hmap.h"

t_list	**get_hmap_buckets(t_hmap m, const char *key)
{
	t_hmap_	*map;
	size_t	index;

	index = get_hmap_index(m, key);
	map = m;
	return (&map->data[index]);
}
