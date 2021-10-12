/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_insert_del.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:23:55 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/28 19:41:05 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_hmap.h"
#include <stdlib.h>

static bool	free_value(t_hmap map, void *value)
{
	t_hmap_	*m;

	m = map;
	m->del(value);
	return (false);
}

bool	ft_hmap_insert_del(t_hmap map, const char *key, void *value)
{
	t_list		*new;
	t_pair		*pair;
	void		*exists;

	exists = ft_hmap_find(map, key);
	if (exists)
		return (free_value(map, value));
	pair = create_pair(key, value);
	if (!pair)
		return (free_value(map, value));
	new = ft_lstnew(pair);
	if (!new)
	{
		free(pair->key);
		free(pair);
		return (free_value(map, value));
	}
	ft_lstadd_back(get_hmap_buckets(map, key), new);
	return (true);
}
