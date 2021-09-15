/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 23:16:36 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/14 20:31:55 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "node.h"
#include "tokenizer.h"
#include <stdlib.h>

// t_node	*get_next_node(t_list **tokens)
// {

// }

t_node	*parse(t_list *tokens)
{
	t_node	*cmds;

	cmds = NULL;
	if (!is_valid_syntax(tokens))
		return (NULL);
	// while (tokens)
	// {
	// 	nodeadd_back(cmds, get_next_node(&tokens));
	// }
	return (cmds);
}
