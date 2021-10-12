/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_copy_cstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 01:49:21 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/25 02:01:56 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_string.h"
#include <stdlib.h>

t_string	ft_str_copy_cstr(t_string dst, const char *src)
{
	char		*cpy;
	t_string_	*d;

	cpy = ft_strdup(src);
	if (!cpy)
		return (NULL);
	d = (t_string_ *)dst;
	free(d->data);
	d->data = cpy;
	d->len = ft_strlen(src);
	d->capacity = d->len + 1;
	return (dst);
}
