/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_sub_cstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 02:11:51 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/06 01:46:09 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	ft_str_sub_cstr(const char *str, size_t index, size_t len)
{
	char	*sub;

	sub = ft_substr(str, index, len);
	if (!sub)
		return (NULL);
	return (ft_str_new(sub));
}
