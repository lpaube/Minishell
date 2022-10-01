#include "libft.h"

bool	ft_isalpha(char c)
{
	return (ft_isupper(c) || ft_islower(c));
}
