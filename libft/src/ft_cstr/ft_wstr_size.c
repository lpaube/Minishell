/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstr_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 00:06:02 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/06 17:03:43 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wstr_size(const wchar_t *s)
{
	size_t	size;

	size = 0;
	while (*s)
		size += ft_wchar_size(*s++);
	return (size);
}
