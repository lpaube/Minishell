/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:14:49 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/30 17:13:02 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"
#include <stdlib.h>

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

void	parse_variable(t_tokenizer *tok, t_string token)
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
		ft_str_append_cstr(token, var_value);
}

bool	parse_special_str(t_tokenizer *tok, t_string token)
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
	return (false);
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
		if (parse_special_str(tok, token))
			continue ;
		ft_str_add_back(token, cursor_char(tok));
		inc_cursor(tok);
	}
	tok->next_token = token;
	if (tok->state == QUOTE)
		print_error("found unclosed quotes");
	else if (tok->state == DQUOTE)
		print_error("found unclosed double quotes");
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
			ft_lstclear(&lst, ft_str_free);
			return (NULL);
		}
		ft_lstadd_back(&lst, ft_lstnew(tok->next_token));
		tok->next_token = NULL;
	}
	return (lst);
}
