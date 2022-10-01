#include "libft.h"

t_string	ft_str_dup_cstr(const char *str)
{
	char	*cpy;

	cpy = ft_strdup(str);
	if (!cpy)
		return (NULL);
	return (ft_str_new(cpy));
}
