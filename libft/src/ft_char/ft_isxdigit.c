#include "libft.h"

bool	ft_isxdigit(char c)
{
	return (ft_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}
