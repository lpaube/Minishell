#include "libft.h"
#include <stdlib.h>

void	ft_strarr_free(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
