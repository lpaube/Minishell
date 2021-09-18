/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operator2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:19:08 by laube             #+#    #+#             */
/*   Updated: 2021/09/18 05:07:00 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <fcntl.h>

void	clean_fd(void)
{
	dup2(g_mini.saved_stdin, 0);
	dup2(g_mini.saved_stdout, 1);
}

void	dest_pipe_write(void)
{
	if (pipe(g_mini.fd) == -1)
		pset_error("Pipe error");
	dup2(g_mini.fd[1], 1);
	close(g_mini.fd[1]);
	g_mini.fd[1] = -1;
}

void	dest_red_output(void)
{
	int			open_fd;
	t_node	*node_og;

	node_og = g_mini.node;
	while (g_mini.node->op == OUTPUT || g_mini.node->op == APPEND)
	{
		if (g_mini.node->op == OUTPUT)
			open_fd = open(g_mini.node->next->name,
					O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (g_mini.node->op == APPEND)
			open_fd = open(g_mini.node->next->name,
					O_RDWR | O_APPEND | O_CREAT, 0644);
		dup2(open_fd, 1);
		close(open_fd);
		execution_control(node_og);
		g_mini.node = g_mini.node->next;
	}
	g_mini.node = g_mini.node->next;
	clean_fd();
}

void	get_dest(void)
{
	if (g_mini.node->op == PIPE)
		dest_pipe_write();
	if (g_mini.node->op == OUTPUT || g_mini.node->op == APPEND)
		dest_red_output();
}
