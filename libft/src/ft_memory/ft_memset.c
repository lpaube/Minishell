#include "libft.h"

void	*ft_memset(void *b, int8_t c, size_t len)
{
	int8_t	*ptr;

	ptr = b;
	while (len-- > 0)
		*ptr++ = c;
	return (b);
}
