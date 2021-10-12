/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:08:24 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/11 22:31:46 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

static bool	is_number(const char *str)
{
	size_t	i;

	i = 0;
	if (*str == '-' || *str == '+')
		++str;
	return (ft_strall(str, ft_isdigit));
}

void	ft_exit(t_node *node)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (ft_strarr_size(node->argv) == 1)
		g_mini.code = SUCCESS;
	else if (!is_number(node->argv[1]))
		pset_err(EXIT, node->argv[1], NUMERIC_REQ, SYNTAX_ERR);
	else if (ft_strarr_size(node->argv) > 2)
	{
		pset_err(EXIT, NULL, TOO_MANY_ARGS, GENERIC_ERR);
		return ;
	}
	else
		g_mini.code = ft_atoi(node->argv[1]) % 256;
	if (node->next)
		return ;
	exit((int)g_mini.code);
}
