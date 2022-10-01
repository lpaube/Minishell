#include "libft.h"

char	ft_toupper(char c)
{
	if (ft_islower(c))
		return (c - ('a' - 'A'));
	return (c);
}
