#include "libft.h"

t_string	ft_str_dup(const t_string str)
{
	return (ft_str_dup_cstr(ft_str_data(str)));
}
