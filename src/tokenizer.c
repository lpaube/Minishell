/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:14:49 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/20 16:56:23 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"
#include <stdlib.h>

static char	*get_quote_str(char **str)
{
	char	*end;
	char	*ret;

	(*str)++;
	end = ft_strchr(*str, '\'');
	if (!end)
		return (NULL);
	ret = ft_substr(*str, 0, end - *str);
	*str = end;
	return (ret);
}

t_list	*tokenize(char *line)
{
	t_list	*lst;
	char	*start;
	char	*str;

	lst = NULL;
	while (*line)
	{
		str = ft_strdup("");
		start = line;
		while (*line && !ft_isspace(*line))
		{
			if (*line != '\'' && *line != '\"')
			{
				++line;
				continue ;
			}
			str = ft_strjoin_free(str, ft_substr(start, 0, line - start));
			if (*line == '\'')
				str = ft_strjoin_free(str, get_quote_str(&line));
			++line;
			start = line;
		}
		if (start != line)
			str = ft_strjoin_free(str, ft_substr(start, 0, line - start));
		if (*str != '\0')
			ft_lstadd_back(&lst, ft_lstnew((void *)str));
		if (*line)
			++line;
	}
	return (lst);
}
