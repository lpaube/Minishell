#include "libft.h"

size_t	ft_numlen(int64_t n, int64_t radix)
{
	size_t	len;

	len = 0;
	while (n / radix != 0)
	{
		n /= radix;
		++len;
	}
	return (len + 1);
}
