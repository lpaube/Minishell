#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	needle_len;

	if (*needle == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	while (*haystack && n >= needle_len)
	{
		if (*haystack == *needle)
		{
			if (ft_strncmp(haystack, needle, needle_len) == 0)
				return ((char *)haystack);
		}
		--n;
		++haystack;
	}
	return (NULL);
}
