/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_add_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:01:22 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/08 13:54:26 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_string.h"
#include <stdlib.h>

static bool	grow_buffer(t_string_ *str)
{
	char	*buf;
	size_t	newsize;

	newsize = (str->capacity + 1UL) * 2UL;
	buf = ft_realloc(str->data,
			str->capacity * sizeof(char),
			newsize * sizeof(char));
	if (!buf)
		return (false);
	str->data = buf;
	str->capacity = newsize;
	return (true);
}

t_string	ft_str_add_back(t_string str, char c)
{
	t_string_	*s;

	s = (t_string_ *)str;
	if (s->len >= s->capacity - 1)
		if (!grow_buffer(s))
			return (NULL);
	s->data[s->len++] = c;
	s->data[s->len] = '\0';
	return (str);
}
