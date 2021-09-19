/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:31:35 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/19 00:31:09 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include <stdio.h>

void	ft_echo(t_node *node)
{
	bool	nl;
	int		i;

	nl = true;
	i = 1;
	while (node->argv[i] && ft_strncmp(node->argv[i], "-n", 3) == 0)
	{
		nl = false;
		++i;
	}
	while (node->argv[i])
	{
		printf("%s", node->argv[i]);
		++i;
		if (node->argv[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
	g_mini.code = SUCCESS;
}
