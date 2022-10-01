#include "libft.h"

size_t	ft_strarr_size(char *const *arr)
{
	size_t	size;

	if (!arr)
		return (0);
	size = 0;
	while (arr[size])
		++size;
	return (size);
}
