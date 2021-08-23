/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:14:49 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/23 12:45:34 by mleblanc         ###   ########.fr       */
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

static char	*get_quote_str(t_tokenizer *tok)
{
	char	*end;
	char	*ret;

	++tok->cursor;
	end = ft_strchr(tok->str + tok->cursor, '\'');
	if (!end)
		return (NULL);
	ret = ft_substr(tok->str, tok->cursor, end - (tok->str + tok->cursor));
	tok->cursor += end - (tok->str + tok->cursor) + 1;
	return (ret);
}

static bool	parse_quote(t_tokenizer *tok, t_token *token)
{
	char	*tmp;

	tmp = get_quote_str(tok);
	if (!tmp)
	{
		free_token(token);
		return (false);
	}
	token->value = ft_strjoin_free(token->value, tmp);
	return (true);
}

static t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	token->value = value;
	token->type = type;
	return (token);
}

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

static void	parse_variable(t_tokenizer *tok, t_token *token)
{
	char			*var_name;
	char			*var_value;
	unsigned int	index;

	++tok->cursor;
	index = tok->cursor;
	while (ft_isalnum(tok->str[index]) || tok->str[index] == '_')
		++index;
	var_name = ft_substr(tok->str, tok->cursor, index - tok->cursor);
	var_value = getenv(var_name);
	free(var_name);
	tok->cursor = index;
	if (var_value)
		token->value = ft_strjoin_free(token->value, ft_strdup(var_value));
}

bool	get_next_token(t_tokenizer *tok)
{
	t_token			*token;
	unsigned int	index;

	if (ft_strchr(OP, tok->str[tok->cursor]))
		return (get_op_token(tok));
	token = new_token(ft_strdup(""), STRING);
	index = tok->cursor;
	while (!ft_strchr(WHITESPACE OP, tok->str[index]))
	{
		if (!ft_strchr("\'\"$", tok->str[index]))
		{
			++index;
			continue ;
		}
		token->value = ft_strjoin_free(token->value,
				ft_substr(tok->str, tok->cursor, index - tok->cursor));
		tok->cursor = index;
		if (tok->str[tok->cursor] == '\'')
			if (!parse_quote(tok, token))
				return (false);
		if (tok->str[tok->cursor] == '$')
			parse_variable(tok, token);
		index = tok->cursor;
	}
	token->value = ft_strjoin_free(token->value,
			ft_substr(tok->str, tok->cursor, index - tok->cursor));
	tok->next_token = token;
	tok->cursor = index;
	return (true);
}

t_list	*tokenize(t_tokenizer *tok)
{
	t_list	*lst;

	lst = NULL;
	while (tok->str[tok->cursor])
	{
		while (ft_strchr(WHITESPACE, tok->str[tok->cursor]))
			++tok->cursor;
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
