#include "libft.h"
#include <stdlib.h>

void	ft_strarr_remove(char **arr, size_t index)
{
	if (index >= ft_strarr_size(arr))
		return ;
	free(arr[index]);
	while (arr[index])
	{
		arr[index] = arr[index + 1];
		++index;
	}
}
