/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:14:49 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/18 19:06:54 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static bool	is_quote(char c)
{
	return (c == '\'');
}

static t_token	*get_quote_token(char **str)
{
	size_t	count;

	count = ft_str_count_if(*str, is_quote);
	if (count % 2 != 0)
		return (NULL);
	return (NULL);
}

static t_token	*get_dquote_token(char **str)
{
	(void)str;
	return (NULL);
}

t_list	*tokenize(char *line)
{
	t_list	*lst;
	t_token	*token;

	lst = NULL;
	while (*line)
	{
		if (*line == '\'')
			token = get_quote_token(&line);
		else if (*line == '\"')
			token = get_dquote_token(&line);
		if (token == NULL)
			return (NULL);
		++line;
	}
	return (lst);
}
