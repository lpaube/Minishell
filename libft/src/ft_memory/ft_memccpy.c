#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int8_t c, size_t n)
{
	int8_t			*d;
	const int8_t	*s;

	d = dst;
	s = src;
	while (n-- > 0)
	{
		*d = *s++;
		if (*d++ == c)
			return (d);
	}
	return (NULL);
}
