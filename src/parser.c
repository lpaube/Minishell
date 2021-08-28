/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 23:16:36 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/28 01:53:45 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "operator.h"
#include <stdlib.h>

void	free_construct(void *c)
{
	t_construct	*construct;

	construct = c;
	free(construct->name);
	ft_free_strarr(construct->args);
	free(construct);
}

t_tree	*get_next_node(t_list **lst)
{
	t_tree		*node;
	t_construct	*construct;
	char		*str;

	if (!*lst)
		return (NULL);
	construct = ft_calloc(1, sizeof(t_construct));
	construct->op = get_operator((*lst)->content);
	construct->name = ft_strdup(ft_str_data((*lst)->content));
	construct->is_cmd = construct->op == NONE;
	construct->args = ft_calloc(1, sizeof(char *));
	*lst = (*lst)->next;
	while (*lst && construct->op == NONE
		&& get_operator((*lst)->content) == NONE)
	{
		str = ft_str_data((*lst)->content);
		construct->args = ft_expand_strarr(construct->args, ft_strdup(str));
		*lst = (*lst)->next;
	}
	node = ft_calloc(1, sizeof(t_tree));
	node->content = construct;
	return (node);
}

t_tree	*parse(t_list *token_lst)
{
	t_tree	*ast;

	ast = get_next_node(&token_lst);
	ast->right = get_next_node(&token_lst);
	return (ast);
}
