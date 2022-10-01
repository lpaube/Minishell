#include "libft.h"

char	*ft_strchr(const char *s, char c)
{
	while (*s != c)
	{
		if (*s++ == '\0')
			return (NULL);
	}
	return ((char *)s);
}
