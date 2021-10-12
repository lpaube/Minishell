/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:15:36 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/20 16:16:34 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_lstall(t_list *lst, bool (*f)(void *))
{
	while (lst)
	{
		if (!f(lst->content))
			return (false);
		lst = lst->next;
	}
	return (true);
}
