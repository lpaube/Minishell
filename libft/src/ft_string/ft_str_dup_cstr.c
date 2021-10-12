/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_dup_cstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 02:02:33 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/25 02:19:33 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	ft_str_dup_cstr(const char *str)
{
	char	*cpy;

	cpy = ft_strdup(str);
	if (!cpy)
		return (NULL);
	return (ft_str_new(cpy));
}
