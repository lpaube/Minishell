/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:57:51 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/09 00:52:58 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int8_t c, size_t n)
{
	int8_t			*d;
	const int8_t	*s;

	d = dst;
	s = src;
	while (n-- > 0)
	{
		*d = *s++;
		if (*d++ == c)
			return (d);
	}
	return (NULL);
}
