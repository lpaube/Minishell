#include "libft.h"

char	*ft_strrchr(const char *s, char c)
{
	const char	*ptr;

	ptr = s + ft_strlen(s);
	while (s <= ptr)
	{
		if (*ptr == c)
			return ((char *)(ptr));
		--ptr;
	}
	return (NULL);
}
