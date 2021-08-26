/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 23:16:36 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/26 03:03:47 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "token.h"
#include "minishell.h"

t_tree	*parse_recurse(t_list *lst)
{
	t_construct	*construct;
	t_token		*token;

	construct = ft_calloc(1, sizeof(t_construct));
	token = (t_token *)lst->content;
	construct->name = ft_strdup(ft_str_data(token->value));
	return (NULL);
}

t_tree	*parse(t_list *token_lst)
{
	// t_tree		*ast;
	t_token		*token;

	token = token_lst->content;
	if (token->type == PIPE)
	{
		unexpected_token(token);
		return (NULL);
	}
	//ast = parse_recurse(token_lst);
	return (ft_calloc(1, 1));
}