#include "libft.h"
#include "ft_string.h"

char	*ft_str_take(t_string str)
{
	t_string_	*ptr;
	char		*ret;

	ptr = str;
	ret = ptr->data;
	ptr->data = NULL;
	ft_str_free(ptr);
	return (ret);
}
