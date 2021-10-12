/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 21:13:43 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/20 03:54:39 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_strarr_remove(char **arr, size_t index)
{
	if (index >= ft_strarr_size(arr))
		return ;
	free(arr[index]);
	while (arr[index])
	{
		arr[index] = arr[index + 1];
		++index;
	}
}
