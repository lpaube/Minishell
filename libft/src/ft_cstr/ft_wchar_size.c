#include "libft.h"

size_t	ft_wchar_size(wchar_t c)
{
	if (c > 0x3FFFFFF)
		return (5);
	if (c > 0xFFFF)
		return (4);
	else if (c > 0x7FF)
		return (3);
	else if (c > 0x7F)
		return (2);
	else
		return (1);
}
