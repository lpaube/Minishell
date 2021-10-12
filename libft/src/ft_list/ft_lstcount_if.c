/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount_if.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:03:21 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/08 16:04:59 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstcount_if(t_list *lst, bool (*f)(void *))
{
	size_t	count;

	count = 0;
	while (lst)
	{
		if (f(lst->content))
			++count;
		ft_lstnext(&lst);
	}
	return (count);
}
