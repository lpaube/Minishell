/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 10:42:07 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/09 00:53:15 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef HASH_SEED
# define HASH_SEED 0
#endif

size_t	ft_hash(const void *b, size_t size)
{
	size_t			hash;
	const int8_t	*ptr;

	hash = HASH_SEED;
	ptr = b;
	while (size--)
		ft_hash_combine(&hash, *ptr++);
	return (hash);
}
