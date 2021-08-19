/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:14:49 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/19 15:51:35 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"
#include <stdlib.h>

static char	*get_quote_str(char **str)
{
	char	*end;
	char	*tmp;
	char	*ret;

	(*str)++;
	end = ft_strchr(*str, '\'');
	if (!end)
		return (NULL);
	tmp = ft_substr(*str, 0, end - *str);
	ret = ft_strtrim(tmp, WHITESPACE);
	free(tmp);
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
			str = ft_strjoin(str, ft_substr(start, 0, line - start));
			if (*line == '\'')
				str = ft_strjoin(str, get_quote_str(&line));
			++line;
			start = line;
		}
		if (start != line)
			str = ft_strjoin(str, ft_substr(start, 0, line - start));
		if (ft_strncmp(str, "", 1) != 0)
			ft_lstadd_back(&lst, ft_lstnew((void *)str));
		free(str);
		++line;
	}
	return (lst);
}
