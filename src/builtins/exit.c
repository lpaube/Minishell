/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:08:24 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/18 16:22:13 by mleblanc         ###   ########.fr       */
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

static void	exec_as_child(void)
{
	pid_t	pid;
	int		code;

	code = g_mini.code;
	pid = fork();
	if (pid == -1)
	{
		pset_err(EXIT, NULL, strerror(errno), GENERIC_ERR);
		return ;
	}
	if (pid == 0)
		exit(code);
	wait(NULL);
}

bool	ft_exit(t_node *node)
{
	if (!node->next)
		ft_putendl_fd(EXIT, STDERR_FILENO);
	if (ft_strarr_size(node->args) == 1)
		g_mini.code = 1;
	else if (!is_number(node->args[1]))
		pset_err(EXIT, node->args[1], NUMERIC_REQ, NON_NUMERIC_ERR);
	else if (ft_strarr_size(node->args) > 2)
	{
		pset_err(EXIT, NULL, TOO_MANY_ARGS, GENERIC_ERR);
		return (false);
	}
	else
		g_mini.code = ft_atoi(node->args[1]) % 256;
	if (node->next)
	{
		exec_as_child();
		return (false);
	}
	return (true);
}
