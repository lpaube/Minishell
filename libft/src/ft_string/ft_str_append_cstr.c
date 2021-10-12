/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_append_cstr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 19:46:12 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/26 18:57:14 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	ft_str_append_cstr(t_string dst, const char *src)
{
	while (*src)
	{
		if (!ft_str_add_back(dst, *src++))
			return (NULL);
	}
	return (dst);
}
