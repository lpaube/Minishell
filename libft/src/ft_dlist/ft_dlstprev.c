/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstprev.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 21:40:16 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/06 01:25:52 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstprev(t_dlist **lst)
{
	if (*lst)
	{
		*lst = (*lst)->prev;
		return (*lst);
	}
	return (NULL);
}
