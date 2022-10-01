#include "libft.h"
#include "ft_string.h"
#include <stdlib.h>

t_string	ft_str_copy_cstr(t_string dst, const char *src)
{
	char		*cpy;
	t_string_	*d;

	cpy = ft_strdup(src);
	if (!cpy)
		return (NULL);
	d = (t_string_ *)dst;
	free(d->data);
	d->data = cpy;
	d->len = ft_strlen(src);
	d->capacity = d->len + 1;
	return (dst);
}
