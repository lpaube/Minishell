#include "ft_hmap.h"
#include <stdlib.h>

t_pair	*create_pair(const char *key, void *value)
{
	t_pair	*pair;

	pair = ft_calloc(1, sizeof(t_pair));
	if (!pair)
		return (NULL);
	pair->key = ft_strdup(key);
	if (!pair->key)
	{
		free(pair);
		return (NULL);
	}
	pair->value = value;
	return (pair);
}
