/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:38:41 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/14 12:51:59 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	appended_redirection(t_phrase **cmds, t_list **tokens)
{
	if (get_operator((*tokens)->content) != NONE
		&& get_operator((*tokens)->content) != PIPE)
	{
		nodeadd_back(cmds, get_operator_first_node(tokens));
		return (true);
	}
	return (false);
}
