/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hmap_index.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:59:04 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/28 19:40:43 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_hmap.h"

size_t	get_hmap_index(t_hmap m, const char *key)
{
	t_hmap_	*map;

	map = m;
	return (ft_hash(key, ft_strlen(key)) % map->size);
}
