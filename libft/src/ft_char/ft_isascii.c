#include "libft.h"

bool	ft_isascii(char c)
{
	return ((c & 0x80) == 0);
}
