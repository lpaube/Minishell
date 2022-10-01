#include "libft.h"

bool	ft_isalnum(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
