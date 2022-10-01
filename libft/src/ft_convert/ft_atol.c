#include "libft.h"

int64_t	ft_atol(const char *str)
{
	int64_t	result;
	int64_t	sign;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	else if (*str == '+')
		++str;
	while (ft_isdigit(*str))
		result = (result * 10) + (*str++ - '0');
	return (result * sign);
}
