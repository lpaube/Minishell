/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 23:16:36 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/27 18:00:15 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "operator.h"

t_tree	*parse_recurse(t_list *lst)
{
	t_construct	*construct;
	t_string	token;

	construct = ft_calloc(1, sizeof(t_construct));
	token = lst->content;
	construct->name = ft_strdup(ft_str_data(token));
	return (NULL);
}

t_tree	*parse(t_list *token_lst)
{
	// t_tree		*ast;
	t_string	token;
	t_operator	op;

	token = token_lst->content;
	op = get_operator(token);
	if (op == PIPE)
	{
		unexpected_token(token);
		return (NULL);
	}
	//ast = parse_recurse(token_lst);
	return (ft_calloc(1, 1));
}
