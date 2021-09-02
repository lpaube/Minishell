/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phrase.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 18:29:47 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/31 18:33:39 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phrase.h"
#include <stdlib.h>

void	nodeclear(t_phrase **lst)
{
	t_phrase	*tmp;

	while (lst && *lst)
	{
		tmp = (*lst)->next;
		free((*lst)->name);
		ft_free_strarr((*lst)->args);
		free(*lst);
		*lst = tmp;
	}
}

t_phrase	*nodelast(t_phrase *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	nodeadd_back(t_phrase **lst, t_phrase *new)
{
	t_phrase	*last;

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

t_operator	get_operator(t_string token)
{
	if (ft_strncmp(ft_str_data(token), "|", ft_str_len(token)) == 0)
		return (PIPE);
	if (ft_strncmp(ft_str_data(token), "<", ft_str_len(token)) == 0)
		return (INPUT);
	if (ft_strncmp(ft_str_data(token), "<<", ft_str_len(token)) == 0)
		return (READ);
	if (ft_strncmp(ft_str_data(token), ">", ft_str_len(token)) == 0)
		return (OUTPUT);
	if (ft_strncmp(ft_str_data(token), ">>", ft_str_len(token)) == 0)
		return (APPEND);
	return (NONE);
}
