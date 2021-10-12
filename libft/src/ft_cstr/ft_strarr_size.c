/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:15:17 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/06 01:13:48 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strarr_size(char *const *arr)
{
	size_t	size;

	if (!arr)
		return (0);
	size = 0;
	while (arr[size])
		++size;
	return (size);
}
