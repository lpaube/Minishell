/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:30:32 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/28 19:40:27 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_hmap.h"
#include <stdlib.h>

static void	remove_elem(t_hmap map, t_list *elem)
{
	t_hmap_	*m;
	t_pair	*pair;

	m = map;
	pair = elem->content;
	delete_pair(pair, m->del);
	free(elem);
}

bool	ft_hmap_remove(t_hmap map, const char *key)
{
	t_list		**buckets;
	t_list		*tmp;
	t_list		*lst;
	t_pair		*pair;

	buckets = get_hmap_buckets(map, key);
	lst = *buckets;
	tmp = NULL;
	while (lst)
	{
		pair = lst->content;
		if (ft_strcmp(key, pair->key) == 0)
		{
			if (tmp)
				tmp->next = lst->next;
			else
				*buckets = lst->next;
			remove_elem(map, lst);
			return (true);
		}
		tmp = lst;
		ft_lstnext(&lst);
	}
	return (false);
}
