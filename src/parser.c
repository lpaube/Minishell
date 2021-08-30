/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 23:16:36 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/30 19:44:03 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "node.h"
#include "operator.h"
#include <stdlib.h>

t_node	*get_next_node(t_list **tokens)
{
	t_node	*node;
	char	*str;

	if (get_operator((*tokens)->content) != NONE)
		return (NULL);
	node = ft_calloc(1, sizeof(t_node));
	node->name = ft_strdup(ft_str_data((*tokens)->content));
	node->args = ft_calloc(1, sizeof(char *));
	while (*tokens && get_operator((*tokens)->content) == NONE)
	{
		str = ft_strdup(ft_str_data((*tokens)->content));
		node->args = ft_expand_strarr(node->args, str);
		*tokens = (*tokens)->next;
	}
	if (*tokens)
	{
		node->op = get_operator((*tokens)->content);
		*tokens = (*tokens)->next;
	}
	else
		node->op = NONE;
	return (node);
}

t_node	*get_operator_first_node(t_list **tokens)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->args = ft_calloc(1, sizeof(char *));
	node->op = get_operator((*tokens)->content);
	*tokens = (*tokens)->next;
	return (node);
}

bool	is_valid_syntax(t_node *cmds)
{
	t_node	*last;

	last = nodelast(cmds);
	if (last->op != NONE)
		return (false);
	return (true);
}

t_node	*parse(t_list *tokens)
{
	t_node	*cmds;
	t_node	*new;

	cmds = NULL;
	if (get_operator(tokens->content) == PIPE)
		return (unexpected_token(tokens->content));
	if (get_operator(tokens->content) != NONE)
		nodeadd_back(&cmds, get_operator_first_node(&tokens));
	while (tokens)
	{
		new = get_next_node(&tokens);
		if (!new)
		{
			nodeclear(&cmds);
			return (unexpected_token(tokens->content));
		}
		nodeadd_back(&cmds, new);
	}
	if (!is_valid_syntax(cmds))
	{
		nodeclear(&cmds);
		return (print_error("parse error near '\\n'"));
	}
	return (cmds);
}
