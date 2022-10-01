#include "libft.h"

char	*ft_ltoa(int64_t n)
{
	return (ft_ltoa_base(n, "0123456789"));
}
