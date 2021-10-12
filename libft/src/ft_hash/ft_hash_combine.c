/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_combine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 10:39:13 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/09 00:52:01 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_hash_combine(size_t *seed, int8_t byte)
{
	*seed ^= (uint32_t)byte + 0x9E3779B9 + (*seed << 6) + (*seed >> 2);
}
