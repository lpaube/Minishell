#include "libft.h"
#include "ft_string.h"

int32_t	ft_str_cmp(const t_string s1, const t_string s2, size_t n)
{
	return (ft_strncmp(ft_str_data(s1), ft_str_data(s2), n));
}
