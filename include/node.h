/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 18:38:34 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/30 18:57:21 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# include "operator.h"

typedef struct s_node
{
	char			*name;
	char			**args;
	t_operator		op;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

void	nodeclear(t_node **node);
void	nodeadd_back(t_node **lst, t_node *new);

#endif
