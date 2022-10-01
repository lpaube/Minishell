#include "libft.h"
#include "ft_string.h"

size_t	ft_str_capacity(t_string str)
{
	t_string_	*s;

	s = (t_string_ *)str;
	return (s->capacity);
}
