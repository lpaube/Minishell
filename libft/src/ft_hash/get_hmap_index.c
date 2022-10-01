#include "libft.h"
#include "ft_hmap.h"

size_t	get_hmap_index(t_hmap m, const char *key)
{
	t_hmap_	*map;

	map = m;
	return (ft_hash(key, ft_strlen(key)) % map->size);
}
