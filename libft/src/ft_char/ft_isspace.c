#include "libft.h"

bool	ft_isspace(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}
