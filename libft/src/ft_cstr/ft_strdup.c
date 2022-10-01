#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*dup;

	size = ft_strlen(s) + 1;
	dup = ft_calloc(size, sizeof(char));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, size * sizeof(char));
	return (dup);
}
