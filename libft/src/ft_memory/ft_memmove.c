#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int8_t			*d;
	const int8_t	*s;

	d = dst;
	s = src;
	if (d < s)
		while (len-- > 0)
			*d++ = *s++;
	else
	{
		d = d + (len - 1);
		s = s + (len - 1);
		while (len-- > 0)
			*d-- = *s--;
	}
	return (dst);
}
