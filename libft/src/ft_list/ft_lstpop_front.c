/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:04:45 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/06 01:24:28 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_lstpop_front(t_list **lst)
{
	t_list	*tmp;
	void	*content;

	if (*lst)
	{
		tmp = (*lst)->next;
		content = (*lst)->content;
		free(*lst);
		*lst = tmp;
		return (content);
	}
	return (NULL);
}
