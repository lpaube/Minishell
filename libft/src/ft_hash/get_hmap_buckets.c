/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hmap_buckets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:32:46 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/28 19:40:10 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_hmap.h"

t_list	**get_hmap_buckets(t_hmap m, const char *key)
{
	t_hmap_	*map;
	size_t	index;

	index = get_hmap_index(m, key);
	map = m;
	return (&map->data[index]);
}
