#include "libft.h"
#include "ft_string.h"
#include <stdlib.h>

void	ft_str_free(t_string str)
{
	t_string_	*s;

	s = (t_string_ *)str;
	if (str)
		free(s->data);
	free(str);
}
