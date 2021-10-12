/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_trim_cstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 02:14:09 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/25 02:17:17 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	ft_str_trim_cstr(const char *str, const char *set)
{
	char	*trim;

	trim = ft_strtrim(str, set);
	if (!trim)
		return (NULL);
	return (ft_str_new(trim));
}
