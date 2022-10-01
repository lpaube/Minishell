#include "libft.h"

int32_t	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const int8_t	*ptr1;
	const int8_t	*ptr2;

	ptr1 = s1;
	ptr2 = s2;
	while (n-- > 0)
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		++ptr1;
		++ptr2;
	}
	return (0);
}
