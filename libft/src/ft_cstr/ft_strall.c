#include "libft.h"

bool	ft_strall(const char *s, bool (*f)(char))
{
	while (*s)
	{
		if (!f(*s))
			return (0);
		++s;
	}
	return (1);
}
