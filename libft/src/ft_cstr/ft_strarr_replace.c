/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 00:19:12 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/19 00:21:41 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_strarr_replace(char **arr, char *new, size_t index)
{
	if (index >= ft_strarr_size(arr))
		return ;
	free(arr[index]);
	arr[index] = new;
}
