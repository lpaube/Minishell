#include "libft.h"
#include "ft_string.h"
#include <stdlib.h>

t_string	ft_str_new_copy(const char *cstr)
{
	char		*copy;
	t_string_	*str;

	copy = ft_strdup(cstr);
	if (!copy)
		return (NULL);
	str = ft_calloc(1, sizeof(t_string_));
	if (!str)
	{
		free(copy);
		return (NULL);
	}
	str->data = copy;
	str->len = ft_strlen(copy);
	str->capacity = str->len + 1;
	return (str);
}
