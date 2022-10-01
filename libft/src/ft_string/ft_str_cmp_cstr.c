#include "libft.h"
#include "ft_string.h"

int32_t	ft_str_cmp_cstr(const t_string s1, const char *s2, size_t n)
{
	return (ft_strncmp(ft_str_data(s1), s2, n));
}
