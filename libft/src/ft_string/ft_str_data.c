#include "libft.h"
#include "ft_string.h"

char	*ft_str_data(t_string str)
{
	t_string_	*s;

	s = (t_string_ *)str;
	return (s->data);
}
