/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 14:47:05 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/06 22:23:07 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	cursor_char(const t_tokenizer *tok)
{
	return (tok->str[tok->cursor]);
}

void	inc_cursor(t_tokenizer *tok)
{
	++tok->cursor;
}

void	eval_quote(t_tokenizer *tok)
{
	if (tok->state == QUOTE)
		tok->state = TEXT;
	else if (tok->state == TEXT)
		tok->state = QUOTE;
}

void	eval_dquote(t_tokenizer *tok)
{
	if (tok->state == DQUOTE)
		tok->state = TEXT;
	else if (tok->state == TEXT)
		tok->state = DQUOTE;
}

bool	end_of_token(const t_tokenizer *tok)
{
	return (tok->state == TEXT
		&& (ft_strchr(WHITESPACE, cursor_char(tok))
			|| ft_strchr(OP, cursor_char(tok))));
}
