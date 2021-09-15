/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operator2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:19:08 by laube             #+#    #+#             */
/*   Updated: 2021/09/15 14:01:08 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	clean_fd(void)
{
	dup2(g_minishell.saved_stdin, 0);
	dup2(g_minishell.saved_stdout, 1);
}

void	dest_pipe_write(void)
{
	if (pipe(g_minishell.fd) == -1)
		print_error("Pipe error");
	dup2(g_minishell.fd[1], 1);
	close(g_minishell.fd[1]);
	g_minishell.fd[1] = -1;
}

void	dest_red_output(void)
{
	int			open_fd;
	t_phrase	*phrase_og;

	phrase_og = g_minishell.phrase;
	while (g_minishell.phrase->op == OUTPUT || g_minishell.phrase->op == APPEND)
	{
		if (g_minishell.phrase->op == OUTPUT)
			open_fd = open(g_minishell.phrase->next->name,
					O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (g_minishell.phrase->op == APPEND)
			open_fd = open(g_minishell.phrase->next->name,
					O_RDWR | O_APPEND | O_CREAT, 0644);
		dup2(open_fd, 1);
		close(open_fd);
		execution_control(phrase_og);
		g_minishell.phrase = g_minishell.phrase->next;
	}
	g_minishell.phrase = g_minishell.phrase->next;
	clean_fd();
}

void	get_dest(void)
{
	if (g_minishell.phrase->op == PIPE)
		dest_pipe_write();
	if (g_minishell.phrase->op == OUTPUT || g_minishell.phrase->op == APPEND)
		dest_red_output();
}
