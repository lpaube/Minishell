#include "libft.h"

t_string	ft_str_trim_cstr(const char *str, const char *set)
{
	char	*trim;

	trim = ft_strtrim(str, set);
	if (!trim)
		return (NULL);
	return (ft_str_new(trim));
}
