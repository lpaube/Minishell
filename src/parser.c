/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 23:16:36 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/28 19:26:09 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "operator.h"
#include <stdlib.h>

char	**get_args(t_list **lst)
{
	char		**args;
	char		*str;
	t_operator	op;

	args = NULL;
	if (*lst)
	{
		op = get_operator((*lst)->content);
		if (op == NONE)
			args = ft_calloc(1, sizeof(char *));
		while (*lst && op == NONE)
		{
			str = ft_str_data((*lst)->content);
			args = ft_expand_strarr(args, ft_strdup(str));
			*lst = (*lst)->next;
			if (*lst)
				op = get_operator((*lst)->content);
		}
	}
	return (args);
}

t_node	*get_next_node(t_list **lst)
{
	t_node	*node;

	if (!*lst)
		return (NULL);
	node = ft_calloc(1, sizeof(t_node));
	node->op = get_operator((*lst)->content);
	if (node->op == NONE)
	{
		node->cmd1 = ft_calloc(1, sizeof(t_cmd));
		node->cmd1->name = ft_strdup(ft_str_data((*lst)->content));
		*lst = (*lst)->next;
		node->cmd1->args = get_args(lst);
		if (*lst)
		{
			node->op = get_operator((*lst)->content);
			*lst = (*lst)->next;
		}
	}
	if (*lst && node->op != NONE)
	{
		node->cmd2 = ft_calloc(1, sizeof(t_cmd));
		node->cmd2->name = ft_strdup(ft_str_data((*lst)->content));
		*lst = (*lst)->next;
		node->cmd2->args = get_args(lst);
	}
	return (node);
}

t_list	*parse(t_list *token_lst)
{
	t_list	*cmds;
	t_node	*node;

	node = get_next_node(&token_lst);
	ft_lstadd_front(&cmds, ft_lstnew(node));
	return (cmds);
}
