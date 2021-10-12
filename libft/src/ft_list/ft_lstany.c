/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstany.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 00:59:54 by mleblanc          #+#    #+#             */
/*   Updated: 2021/06/29 01:01:41 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_lstany(t_list *lst, bool (*f)(void *))
{
	while (lst)
	{
		if (f(lst->content))
			return (true);
		lst = lst->next;
	}
	return (false);
}
