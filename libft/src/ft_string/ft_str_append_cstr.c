#include "libft.h"

t_string	ft_str_append_cstr(t_string dst, const char *src)
{
	while (*src)
	{
		if (!ft_str_add_back(dst, *src++))
			return (NULL);
	}
	return (dst);
}
