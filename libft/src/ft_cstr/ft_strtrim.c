#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char		*ret;
	const char	*end;
	size_t		len;

	while (*s1 && ft_strchr(set, *s1))
		++s1;
	end = s1 + ft_strlen(s1) - 1;
	while (end > s1 && ft_strchr(set, *end))
		--end;
	len = (size_t)end - (size_t)s1 + 1;
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s1, len * sizeof(char));
	return (ret);
}
