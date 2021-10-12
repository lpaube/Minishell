/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 10:58:32 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/28 19:38:56 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_hmap.h"
#include <stdlib.h>

t_hmap	ft_hmap_new(size_t size, void (*del)(void *))
{
	t_hmap_	*map;

	map = ft_calloc(1, sizeof(t_hmap_));
	if (!map)
		return (NULL);
	map->data = ft_calloc(size, sizeof(t_list *));
	if (!map->data)
	{
		free(map);
		return (NULL);
	}
	map->size = size;
	map->del = del;
	return (map);
}
