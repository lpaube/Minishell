#include "libft.h"

t_string	ft_str_append(t_string dst, const t_string src)
{
	return (ft_str_append_cstr(dst, ft_str_data(src)));
}
