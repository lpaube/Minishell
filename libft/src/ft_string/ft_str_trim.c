#include "libft.h"

t_string	ft_str_trim(const t_string str, const char *set)
{
	return (ft_str_trim_cstr(ft_str_data(str), set));
}
