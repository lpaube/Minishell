#include "libft.h"

#ifndef HASH_SEED
# define HASH_SEED 0
#endif

size_t	ft_hash(const void *b, size_t size)
{
	size_t			hash;
	const int8_t	*ptr;

	hash = HASH_SEED;
	ptr = b;
	while (size--)
		ft_hash_combine(&hash, *ptr++);
	return (hash);
}
