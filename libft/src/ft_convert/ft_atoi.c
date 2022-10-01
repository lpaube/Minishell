#include "libft.h"

int32_t	ft_atoi(const char *str)
{
	int32_t	result;
	int32_t	sign;

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
