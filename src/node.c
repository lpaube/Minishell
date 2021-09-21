/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:39:19 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/21 00:18:26 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include <stdlib.h>

static void	free_redir(void *redir)
{
	t_redir	*r;

	r = redir;
	free(r->file);
	free(redir);
}

void	nodeclear(t_node **lst)
{
	t_node	*tmp;

	while (lst && *lst)
	{
		tmp = (*lst)->next;
		ft_strarr_free((*lst)->argv);
		ft_lstclear(&(*lst)->redirs, free_redir);
		free(*lst);
		*lst = tmp;
	}
}

t_node	*nodelast(t_node *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	nodeadd_back(t_node **lst, t_node *new)
{
	t_node	*last;

	if (lst)
	{
		if (*lst)
		{
			last = nodelast(*lst);
			last->next = new;
			if (new)
				new->prev = last;
		}
		else
			*lst = new;
	}
}

t_node	*nodenew(void)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->argv = ft_calloc(1, sizeof(char *));
	return (node);
}
