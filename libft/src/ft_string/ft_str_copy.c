#include "libft.h"

t_string	ft_str_copy(t_string dst, const t_string src)
{
	return (ft_str_copy_cstr(dst, ft_str_data(src)));
}
