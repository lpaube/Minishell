/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:14:49 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/23 18:45:49 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"
#include <stdlib.h>

#define OP ">|<"

void	free_token(void *t)
{
	free(((t_token *)t)->value);
	free(t);
}

// static char	*get_quote_str(t_tokenizer *tok)
// {
// 	char	*end;
// 	char	*ret;

// 	++tok->cursor;
// 	end = ft_strchr(tok->str + tok->cursor, '\'');
// 	if (!end)
// 		return (NULL);
// 	ret = ft_substr(tok->str, tok->cursor, end - (tok->str + tok->cursor));
// 	tok->cursor += end - (tok->str + tok->cursor) + 1;
// 	return (ret);
// }

// static bool	parse_quote(t_tokenizer *tok, t_token *token)
// {
// 	char	*tmp;

// 	tmp = get_quote_str(tok);
// 	if (!tmp)
// 	{
// 		free_token(token);
// 		return (false);
// 	}
// 	token->value = ft_strjoin_free(token->value, tmp);
// 	return (true);
// }

static t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	token->value = value;
	token->type = type;
	return (token);
}

// static char	*get_dquote_str(t_tokenizer *tok)
// {
// 	char			*end;
// 	char			*ret;
// 	unsigned int	index;

// 	index = ++tok->cursor;
// 	end = ft_strchr(tok->str + index, '\"');
// 	while (end && *(end - 1) == '\\')
// 		end = ft_strchr(tok->str + index, '\"');
// }

static bool	get_op_token(t_tokenizer *tok)
{
	t_token			*token;
	unsigned int	index;

	index = tok->cursor;
	if (ft_strchr("<>", tok->str[index + 1])
		&& ft_strchr("<>", tok->str[index]))
		++index;
	token = new_token(
			ft_substr(tok->str, tok->cursor, index - tok->cursor + 1),
			OPERATOR);
	tok->cursor = index + 1;
	tok->next_token = token;
	return (true);
}

// static void	parse_variable(t_tokenizer *tok, t_token *token)
// {
// 	char			*var_name;
// 	char			*var_value;
// 	unsigned int	index;

// 	if (tok->str[tok->cursor + 1] == '?')
// 			;
// 	index = ++tok->cursor;
// 	while (ft_isalnum(tok->str[index]) || tok->str[index] == '_')
// 		++index;
// 	var_name = ft_substr(tok->str, tok->cursor, index - tok->cursor);
// 	var_value = getenv(var_name);
// 	free(var_name);
// 	tok->cursor = index;
// 	if (var_value)
// 		token->value = ft_strjoin_free(token->value, ft_strdup(var_value));
// }

static void	set_state(t_tokenizer *tok, t_state state)
{
	tok->last_state = tok->state;
	tok->state = state;
}

static char	cursor_char(t_tokenizer *tok)
{
	return (tok->str[tok->cursor]);
}

bool	get_next_token(t_tokenizer *tok)
{
	t_token			*token;
	t_string		*str;

	if (ft_strchr(OP, cursor_char(tok)))
		return (get_op_token(tok));
	token = new_token(NULL, STRING);
	str = ft_string_new(NULL);
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
		ft_string_add_back(str, cursor_char(tok));
		++tok->cursor;
	}
	token->value = str->data;
	tok->next_token = token;
	str->data = NULL;
	ft_string_clear(str);
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
