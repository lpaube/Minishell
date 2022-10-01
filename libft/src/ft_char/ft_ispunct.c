#include "libft.h"

bool	ft_ispunct(char c)
{
	return (ft_isprint(c) && c != ' ' && !ft_isalnum(c));
}
