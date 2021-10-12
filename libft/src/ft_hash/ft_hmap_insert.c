/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:18:10 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/28 19:39:38 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_hmap.h"
#include <stdlib.h>

bool	ft_hmap_insert(t_hmap map, const char *key, void *value)
{
	t_list		*new;
	t_pair		*pair;
	void		*exists;

	exists = ft_hmap_find(map, key);
	if (exists)
		return (false);
	pair = create_pair(key, value);
	if (!pair)
		return (false);
	new = ft_lstnew(pair);
	if (!new)
	{
		free(pair->key);
		free(pair);
		return (false);
	}
	ft_lstadd_back(get_hmap_buckets(map, key), new);
	return (true);
}
