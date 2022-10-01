#include "libft.h"
#include "ft_string.h"
#include <stdlib.h>

t_string	ft_str_new(char *cstr)
{
	t_string_	*str;

	str = ft_calloc(1, sizeof(t_string_));
	if (!str)
		return (NULL);
	if (!cstr)
	{
		str->data = ft_calloc(INITIAL_CAPACITY, sizeof(char));
		if (!str->data)
		{
			free(str);
			return (NULL);
		}
		str->capacity = INITIAL_CAPACITY;
		return ((t_string)str);
	}
	str->data = cstr;
	str->len = ft_strlen(cstr);
	str->capacity = str->len + 1;
	return ((t_string)str);
}
