#include "libft.h"

size_t	ft_strcount_if(const char *s, bool (*f)(char))
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (f(*s))
			++count;
		++s;
	}
	return (count);
}
