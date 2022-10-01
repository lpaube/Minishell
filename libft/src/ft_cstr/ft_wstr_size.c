#include "libft.h"

size_t	ft_wstr_size(const wchar_t *s)
{
	size_t	size;

	size = 0;
	while (*s)
		size += ft_wchar_size(*s++);
	return (size);
}
