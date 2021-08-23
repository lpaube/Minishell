/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:14:49 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/23 19:04:45 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"
#include <stdlib.h>

#define OP ">|<"

void	free_token(void *t)
{
	ft_string_clear(((t_token *)t)->value);
	free(t);
}

static t_token	*new_token(t_string *value, t_token_type type)
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

static bool	get_op_token(t_tokenizer *tok)
{
	t_token		*token;
	char		first_char;

	token = new_token(ft_string_new(NULL), OPERATOR);
	first_char = cursor_char(tok);
	ft_string_add_back(token->value, first_char);
	++tok->cursor;
	if (ft_strchr(OP, first_char) && first_char == cursor_char(tok))
	{
		ft_string_add_back(token->value, first_char);
		++tok->cursor;
	}
	tok->next_token = token;
	return (true);
}

static void	set_state(t_tokenizer *tok, t_state state)
{
	tok->last_state = tok->state;
	tok->state = state;
}

bool	get_next_token(t_tokenizer *tok)
{
	t_token			*token;

	if (ft_strchr(OP, cursor_char(tok)))
		return (get_op_token(tok));
	token = new_token(ft_string_new(NULL), STRING);
	while (!ft_strchr(WHITESPACE OP, cursor_char(tok)))
	{
		if (cursor_char(tok) == '\'')
		{
			if (tok->state == QUOTE)
				set_state(tok, TEXT);
			else
				set_state(tok, QUOTE);
			++tok->cursor;
			continue ;
		}
		else if (cursor_char(tok) == '\"')
		{
			set_state(tok, DQUOTE);
			++tok->cursor;
			continue ;
		}
		else if (cursor_char(tok) == '$')
		{
			set_state(tok, VARIABLE);
			++tok->cursor;
			continue ;
		}
		ft_string_add_back(token->value, cursor_char(tok));
		++tok->cursor;
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
			++tok->cursor;
		if (!get_next_token(tok))
		{
			ft_lstclear(&lst, free_token);
			return (NULL);
		}
		ft_lstadd_back(&lst, ft_lstnew(tok->next_token));
		tok->next_token = NULL;
	}
	if (tok->state == QUOTE || tok->state == DQUOTE)
		ft_lstclear(&lst, free_token);
	return (lst);
}
