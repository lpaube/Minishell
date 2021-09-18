/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operator1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:54:03 by laube             #+#    #+#             */
/*   Updated: 2021/09/18 05:06:55 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <fcntl.h>

void	src_pipe_read(void)
{
	dup2(g_mini.fd[0], 0);
	close(g_mini.fd[0]);
	g_mini.fd[0] = -1;
}

void	src_red_input(void)
{
	int		open_fd;
	char	*line;

	open_fd = open(g_mini.node->next->name, O_RDONLY);
	while (get_next_line(open_fd, &line) > 0)
	{
		ft_putstr_fd(line, g_mini.fd[1]);
		ft_putstr_fd("\n", g_mini.fd[1]);
		free(line);
	}
	free(line);
	close(open_fd);
}

void	src_heredoc(void)
{
	char	*line;
	char	*limiter;

	if (g_mini.node->next)
		limiter = g_mini.node->next->name;
	else
		limiter = NULL;
	ft_putstr_fd("> ", 1);
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			return ;
		}
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(line, g_mini.fd[1]);
		ft_putstr_fd("\n", g_mini.fd[1]);
		free(line);
	}
}

void	get_source(void)
{
	t_node	*node_og;

	node_og = g_mini.node;
	if (g_mini.node->prev && g_mini.node->prev->op == PIPE)
		src_pipe_read();
	if (g_mini.node->op == INPUT || g_mini.node->op == HEREDOC)
	{
		if (pipe(g_mini.fd) != 0)
			pset_error("pipe failed in src_heredoc");
		while (g_mini.node->op == INPUT
			|| g_mini.node->op == READ)
		{
			if (g_mini.node->op == INPUT)
				src_red_input();
			if (g_mini.node->op == READ)
				src_heredoc();
			g_mini.node = g_mini.node->next;
		}
		dup2(g_mini.fd[0], 0);
		g_mini.fd[0] = -1;
		close(g_mini.fd[1]);
		g_mini.fd[1] = -1;
	}
	g_mini.node = node_og;
}

int	operation_control(void)
{
	get_source();
	get_dest();
	if (execution_control(g_mini.node) == 1)
		return (1);
	clean_fd();
	while (g_mini.node->op == INPUT || g_mini.node->op == HEREDOC)
		g_mini.node = g_mini.node->next;
	return (0);
}
