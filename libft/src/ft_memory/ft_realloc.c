/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:07:04 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/09 00:51:39 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t oldsize, size_t size)
{
	int8_t	*newptr;

	if (!ptr)
		return (ft_calloc(size, 1));
	if (size == 0 || oldsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (oldsize == size)
		return (ptr);
	newptr = ft_calloc(size, 1);
	if (!newptr)
		return (NULL);
	if (oldsize < size)
		size = oldsize;
	ft_memcpy(newptr, ptr, size);
	free(ptr);
	return (newptr);
}
