/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:31:35 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/28 18:34:49 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	free_cmd(void *cmd)
{
	t_cmd	*c;

	c = cmd;
	free(c->name);
	ft_free_strarr(c->args);
}

void	free_node(void *node)
{
	t_node	*n;

	n = node;
	free_cmd(n->cmd1);
	free_cmd(n->cmd2);
	free(n);
}
