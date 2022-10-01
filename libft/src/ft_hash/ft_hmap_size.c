#include "libft.h"
#include "ft_hmap.h"

size_t	ft_hmap_size(t_hmap m)
{
	t_hmap_	*map;

	map = m;
	return (map->size);
}
