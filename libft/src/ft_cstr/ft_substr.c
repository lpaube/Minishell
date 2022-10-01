#include "libft.h"

char	*ft_substr(const char *s, size_t start, size_t len)
{
	size_t	newlen;
	size_t	strlen;
	char	*substr;

	strlen = ft_strlen(s);
	newlen = 0;
	if (strlen > start)
		newlen = ft_strnlen(s + start, len);
	else
		start = (unsigned int)strlen;
	substr = ft_calloc(newlen + 1, sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, (newlen + 1) * sizeof(char));
	return (substr);
}
