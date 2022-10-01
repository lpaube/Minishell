#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- > 0)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		if (*s1 == '\0')
			break ;
		++s1;
		++s2;
	}
	return (0);
}
