/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:14:49 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/24 18:06:43 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"
#include <stdlib.h>

static bool	get_operator_token(t_tokenizer *tok)
{
	t_token		*token;
	char		first_char;

	token = new_token(ft_strnew(NULL), OPERATOR);
	first_char = cursor_char(tok);
	ft_stradd_back(token->value, first_char);
	inc_cursor(tok);
	if (ft_strchr(OP, first_char) && first_char == cursor_char(tok))
	{
		ft_stradd_back(token->value, first_char);
		inc_cursor(tok);
	}
	tok->next_token = token;
	return (true);
}

void	parse_variable(t_tokenizer *tok, t_token *token)
{
	t_string	var_name;
	char		*var_value;

	inc_cursor(tok);
	var_name = ft_strnew(NULL);
	while (ft_isalnum(cursor_char(tok)) || cursor_char(tok) == '_')
	{
		ft_stradd_back(var_name, cursor_char(tok));
		inc_cursor(tok);
	}
	var_value = getenv(ft_strdata(var_name));
	ft_strfree(var_name);
	if (var_value)
		ft_strappend_cstr(token->value, var_value);
	else
		ft_strappend_cstr(token->value, "");
}

static bool	parse_special_str(t_tokenizer *tok, t_token *token)
{
	if (cursor_char(tok) == '\'' && tok->state != DQUOTE)
	{
		eval_quote(tok);
		return (true);
	}
	else if (cursor_char(tok) == '\"' && tok->state != QUOTE)
	{
		eval_dquote(tok);
		return (true);
	}
	else if (cursor_char(tok) == '$' && tok->state != QUOTE)
	{
		parse_variable(tok, token);
		return (true);
	}
	else if (cursor_char(tok) == '\\' && tok->state == DQUOTE)
		if (ft_strchr("\"?\\", tok->str[tok->cursor + 1]))
			inc_cursor(tok);
	return (false);
}

bool	get_next_token(t_tokenizer *tok)
{
	t_token	*token;

	if (ft_strchr(OP, cursor_char(tok)))
		return (get_operator_token(tok));
	token = new_token(ft_strnew(NULL), STRING);
	while (cursor_char(tok))
	{
		if (end_of_token(tok))
			break ;
		if (parse_special_str(tok, token))
			continue ;
		ft_stradd_back(token->value, cursor_char(tok));
		inc_cursor(tok);
	}
	tok->next_token = token;
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
			ft_lstclear(&lst, free_token);
			return (NULL);
		}
		ft_lstadd_back(&lst, ft_lstnew(tok->next_token));
		tok->next_token = NULL;
	}
	return (lst);
}
