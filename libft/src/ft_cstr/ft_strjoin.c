#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*newstr;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = ft_calloc(size, sizeof(char));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, size * sizeof(char));
	ft_strlcat(newstr, s2, size * sizeof(char));
	return (newstr);
}
