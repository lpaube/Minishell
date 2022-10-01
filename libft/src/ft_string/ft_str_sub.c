#include "libft.h"

t_string	ft_str_sub(t_string str, size_t index, size_t len)
{
	return (ft_str_sub_cstr(ft_str_data(str), index, len));
}
