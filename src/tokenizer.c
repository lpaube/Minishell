/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:14:49 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/25 23:25:51 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"
#include <stdlib.h>

bool	get_operator_token(t_tokenizer *tok)
{
	t_token		*token;
	char		first_char;

	token = new_token(ft_str_new(NULL), OPERATOR);
	first_char = cursor_char(tok);
	ft_str_add_back(token->value, first_char);
	inc_cursor(tok);
	if (ft_strchr(OP, first_char) && first_char == cursor_char(tok))
	{
		ft_str_add_back(token->value, first_char);
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
	var_name = ft_str_new(NULL);
	while (ft_isalnum(cursor_char(tok)) || cursor_char(tok) == '_')
	{
		ft_str_add_back(var_name, cursor_char(tok));
		inc_cursor(tok);
	}
	var_value = getenv(ft_str_data(var_name));
	ft_str_free(var_name);
	if (var_value)
		ft_str_append_cstr(token->value, var_value);
}

bool	parse_special_str(t_tokenizer *tok, t_token *token)
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
	token = new_token(ft_str_new(NULL), STRING);
	while (cursor_char(tok))
	{
		if (end_of_token(tok))
			break ;
		if (parse_special_str(tok, token))
			continue ;
		ft_str_add_back(token->value, cursor_char(tok));
		inc_cursor(tok);
	}
	tok->next_token = token;
	if (tok->state == QUOTE)
		print_error("Found unclosed quotes");
	else if (tok->state == DQUOTE)
		print_error("Found unclosed double quotes");
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
