/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreeclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 01:38:28 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/06 01:26:34 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_treeclear(t_btree **tree, void (*del)(void *))
{
	if (*tree)
	{
		if ((*tree)->left)
			ft_treeclear(&(*tree)->left, del);
		if ((*tree)->right)
			ft_treeclear(&(*tree)->right, del);
		del((*tree)->content);
		free(*tree);
		*tree = NULL;
	}
}
