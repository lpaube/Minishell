#include "libft.h"
#include <stdlib.h>

void	ft_strarr_replace(char **arr, char *new, size_t index)
{
	if (index >= ft_strarr_size(arr))
		return ;
	free(arr[index]);
	arr[index] = new;
}
