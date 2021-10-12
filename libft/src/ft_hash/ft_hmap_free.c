/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:14:11 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/28 19:42:35 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_hmap.h"
#include <stdlib.h>

void	ft_hmap_free(t_hmap map)
{
	t_hmap_	*m;
	size_t	i;
	t_list	*lst;
	t_list	*tmp;

	m = map;
	i = 0;
	while (i < m->size)
	{
		lst = m->data[i];
		while (lst)
		{
			tmp = lst->next;
			delete_pair(lst->content, m->del);
			free(lst);
			lst = tmp;
		}
		++i;
	}
	free(m->data);
	free(m);
}
