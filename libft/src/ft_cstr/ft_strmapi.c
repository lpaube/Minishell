#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(uint32_t, char))
{
	uint32_t	i;
	char		*ret;

	ret = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = f(i, s[i]);
		++i;
	}
	return (ret);
}
