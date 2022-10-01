#include "libft.h"

void	*ft_memchr(const void *s, int8_t c, size_t n)
{
	const int8_t	*ptr;

	ptr = s;
	while (n-- > 0)
	{
		if (*ptr == c)
			return ((void *)ptr);
		++ptr;
	}
	return (NULL);
}
