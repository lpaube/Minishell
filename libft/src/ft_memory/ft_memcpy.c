#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int8_t			*d;
	const int8_t	*s;

	d = dst;
	s = src;
	while (n-- > 0)
		*d++ = *s++;
	return (dst);
}
