/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 18:49:21 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/09 00:51:39 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int8_t c, size_t n)
{
	const int8_t	*ptr;

	ptr = s;
	while (n-- > 0)
	{
		if (*ptr == c)
			return ((void *)ptr);
		++ptr;
	}
	return (NULL);
}
