#include "libft.h"
#include "ft_string.h"

t_string	ft_str_clear(t_string str)
{
	t_string_	*s;

	s = (t_string_ *)str;
	ft_bzero(s->data, s->capacity);
	s->len = 0;
	return (str);
}
