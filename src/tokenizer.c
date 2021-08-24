/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:14:49 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/23 23:14:20 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"
#include <stdlib.h>

#define OP ">|<"

void	free_token(void *t)
{
	ft_strfree(((t_token *)t)->value);
	free(t);
}

static t_token	*new_token(t_string value, t_token_type type)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	token->value = value;
	token->type = type;
	return (token);
}

static char	cursor_char(t_tokenizer *tok)
{
	return (tok->str[tok->cursor]);
}

static void	inc_cursor(t_tokenizer *tok)
{
	++tok->cursor;
}

static bool	get_op_token(t_tokenizer *tok)
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

static void	set_state(t_tokenizer *tok, t_state state)
{
	tok->last_state = tok->state;
	tok->state = state;
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
	ft_strappend_cstr(token->value, var_value);
}

bool	get_next_token(t_tokenizer *tok)
{
	t_token	*token;

	if (ft_strchr(OP, cursor_char(tok)))
		return (get_op_token(tok));
	token = new_token(ft_strnew(NULL), STRING);
	while (cursor_char(tok))
	{
		if (tok->state == TEXT
			&& (ft_strchr(WHITESPACE, cursor_char(tok))
				|| ft_strchr(OP, cursor_char(tok))))
			break ;
		if (cursor_char(tok) == '\'' && tok->state != DQUOTE)
		{
			if (tok->state == QUOTE)
				set_state(tok, TEXT);
			else
				set_state(tok, QUOTE);
			inc_cursor(tok);
			continue ;
		}
		else if (cursor_char(tok) == '\"' && tok->state != QUOTE)
		{
			if (tok->state == DQUOTE)
				set_state(tok, TEXT);
			else
				set_state(tok, DQUOTE);
			inc_cursor(tok);
			continue ;
		}
		else if (cursor_char(tok) == '$' && tok->state != QUOTE)
		{
			parse_variable(tok, token);
			continue ;
		}
		ft_stradd_back(token->value, cursor_char(tok));
		inc_cursor(tok);
	}
	tok->next_token = token;
	return (true);
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
	if (tok->state != TEXT)
		ft_lstclear(&lst, free_token);
	return (lst);
}
