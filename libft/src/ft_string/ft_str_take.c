/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_take.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:20:57 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/16 22:04:33 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_string.h"

char	*ft_str_take(t_string str)
{
	t_string_	*ptr;
	char		*ret;

	ptr = str;
	ret = ptr->data;
	ptr->data = NULL;
	ft_str_free(ptr);
	return (ret);
}
