/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:39:19 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/14 20:01:45 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include <stdlib.h>

static void	free_redir(void *redir)
{
	t_redir	*r;

	r = redir;
	free(r->file);
}

void	nodeclear(t_node **lst)
{
	t_node	*tmp;

	while (lst && *lst)
	{
		tmp = (*lst)->next;
		free((*lst)->cmd);
		ft_free_strarr((*lst)->args);
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

t_type	get_type(t_string token)
{
	if (ft_strncmp(ft_str_data(token), "|", ft_str_len(token)) == 0)
		return (PIPE);
	if (ft_strncmp(ft_str_data(token), "<", ft_str_len(token)) == 0)
		return (INPUT);
	if (ft_strncmp(ft_str_data(token), "<<", ft_str_len(token)) == 0)
		return (HEREDOC);
	if (ft_strncmp(ft_str_data(token), ">", ft_str_len(token)) == 0)
		return (OUTPUT);
	if (ft_strncmp(ft_str_data(token), ">>", ft_str_len(token)) == 0)
		return (APPEND);
	return (STRING);
}
