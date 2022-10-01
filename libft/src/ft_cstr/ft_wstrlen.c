#include "libft.h"

size_t	ft_wstrlen(const wchar_t *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		++len;
	return (len);
}
