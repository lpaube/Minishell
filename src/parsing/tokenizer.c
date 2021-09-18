/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:14:49 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/17 23:37:49 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "eprint.h"
#include "minishell.h"
#include <stdlib.h>

void	init_tokenizer(t_tokenizer *tok)
{
	tok->cursor = 0;
	tok->state = TEXT;
	tok->next_token = NULL;
	tok->str = NULL;
}

bool	get_operator_token(t_tokenizer *tok)
{
	t_string	token;
	char		first_char;

	token = ft_str_new(NULL);
	first_char = cursor_char(tok);
	ft_str_add_back(token, first_char);
	inc_cursor(tok);
	if (ft_strchr("<>", first_char) && first_char == cursor_char(tok))
	{
		ft_str_add_back(token, first_char);
		inc_cursor(tok);
	}
	tok->next_token = token;
	return (true);
}

bool	get_next_token(t_tokenizer *tok)
{
	t_string	token;

	if (ft_strchr(OP, cursor_char(tok)))
		return (get_operator_token(tok));
	token = ft_str_new(NULL);
	while (cursor_char(tok))
	{
		if (end_of_token(tok))
			break ;
		if (cursor_char(tok) == '\'')
			eval_quote(tok);
		else if (cursor_char(tok) == '\"')
			eval_dquote(tok);
		ft_str_add_back(token, cursor_char(tok));
		inc_cursor(tok);
	}
	tok->next_token = token;
	if (tok->state == QUOTE)
		pset_err(SHELL_NAME, NULL, "found unclosed quotes", SYNTAX_ERR);
	else if (tok->state == DQUOTE)
		pset_err(SHELL_NAME, NULL, "found unclosed double quotes", SYNTAX_ERR);
	return (tok->state == TEXT);
}

t_list	*tokenize(t_tokenizer *tok)
{
	t_list	*lst;

	lst = NULL;
	while (cursor_char(tok))
	{
		while (ft_strchr(WHITESPACE, cursor_char(tok)))
			inc_cursor(tok);
		if (!get_next_token(tok))
		{
			ft_str_free(tok->next_token);
			ft_lstclear(&lst, ft_str_free);
			return (NULL);
		}
		ft_lstadd_back(&lst, ft_lstnew(tok->next_token));
		tok->next_token = NULL;
	}
	return (lst);
}
