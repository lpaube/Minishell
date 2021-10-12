/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_new_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:53:57 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/15 16:56:11 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_string.h"
#include <stdlib.h>

t_string	ft_str_new_copy(const char *cstr)
{
	char		*copy;
	t_string_	*str;

	copy = ft_strdup(cstr);
	if (!copy)
		return (NULL);
	str = ft_calloc(1, sizeof(t_string_));
	if (!str)
	{
		free(copy);
		return (NULL);
	}
	str->data = copy;
	str->len = ft_strlen(copy);
	str->capacity = str->len + 1;
	return (str);
}
