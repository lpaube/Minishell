#include "libft.h"

void	ft_hash_combine(size_t *seed, int8_t byte)
{
	*seed ^= (uint32_t)byte + 0x9E3779B9 + (*seed << 6) + (*seed >> 2);
}
