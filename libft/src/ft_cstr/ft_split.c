/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:27:20 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/06 01:11:17 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*word_start(const char **s, char delim)
{
	while (**s && **s == delim)
		++(*s);
	return ((char *)*s);
}

static char	*word_end(const char **s, char delim)
{
	while (**s && **s != delim)
		++(*s);
	return ((char *)*s);
}

static size_t	count_words(const char *s, char delim)
{
	size_t		count;
	const char	*w_start;
	const char	*w_end;

	count = 0;
	while (*s)
	{
		w_start = word_start(&s, delim);
		w_end = word_end(&s, delim);
		if (w_start != w_end)
			++count;
	}
	return (count);
}

static bool	append_words(char **arr, const char *s, char delim)
{
	const char	*w_start;
	const char	*w_end;
	size_t		i;

	i = 0;
	while (*s)
	{
		w_start = word_start(&s, delim);
		w_end = word_end(&s, delim);
		if (w_start != w_end)
		{
			arr[i] = ft_substr(w_start, 0, (size_t)w_end - (size_t)w_start);
			if (!arr[i])
				return (false);
		}
		++i;
	}
	return (true);
}

char	**ft_split(const char *s, char delim)
{
	char	**ret;
	size_t	word_count;

	word_count = count_words(s, delim);
	ret = ft_calloc(word_count + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	if (!append_words(ret, s, delim))
	{
		ft_strarr_free(ret);
		return (NULL);
	}
	return (ret);
}
