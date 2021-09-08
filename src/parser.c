/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 23:16:36 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/08 12:49:37 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "phrase.h"
#include "tokenizer.h"
#include <stdlib.h>

t_phrase	*get_next_node(t_list **tokens)
{
	t_phrase	*node;
	char		*str;

	if (get_operator((*tokens)->content) != NONE)
		return (NULL);
	node = ft_calloc(1, sizeof(t_phrase));
	node->name = ft_strdup(ft_str_data((*tokens)->content));
	node->args = ft_calloc(1, sizeof(char *));
	while (*tokens && get_operator((*tokens)->content) == NONE)
	{
		str = ft_strdup(ft_str_data((*tokens)->content));
		node->args = ft_expand_strarr(node->args, str);
		ft_lstnext(tokens);
	}
	if (*tokens)
	{
		node->op = get_operator((*tokens)->content);
		ft_lstnext(tokens);
	}
	else
		node->op = NONE;
	return (node);
}

t_phrase	*get_operator_first_node(t_list **tokens)
{
	t_phrase	*node;

	node = ft_calloc(1, sizeof(t_phrase));
	node->args = ft_calloc(1, sizeof(char *));
	node->op = get_operator((*tokens)->content);
	if (node->op == READ || node->op == APPEND
		|| node->op == INPUT || node->op == READ)
	{
		node->name = ft_strdup("cat");
		node->args = ft_expand_strarr(node->args, ft_strdup("cat"));
	}
	ft_lstnext(tokens);
	return (node);
}

bool	is_valid_syntax(t_phrase *cmds)
{
	t_phrase	*last;

	last = nodelast(cmds);
	if (last->op != NONE)
		return (false);
	return (true);
}

void	fix_redirections(t_phrase *cmds)
{
	int	i;

	while (cmds)
	{
		if (cmds->op == OUTPUT || cmds->op == APPEND || cmds->op == INPUT || cmds->op == READ)
		{
			if (cmds->next && ft_strarr_size(cmds->next->args) > 1)
			{
				i = 1;
				while (cmds->next->args[i])
				{
					cmds->args = ft_expand_strarr(cmds->args,
						cmds->next->args[i]);
					cmds->next->args[i] = NULL;
					++i;
				}
			}
		}
		cmds = cmds->next;
	}
}

t_phrase	*parse(t_list *tokens)
{
	t_phrase	*cmds;
	t_phrase	*new;

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
		return (print_error("syntax error near unexpected token '\\n'"));
	}
	fix_redirections(cmds);
	return (cmds);
}
