/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:54:03 by laube             #+#    #+#             */
/*   Updated: 2021/09/08 23:32:04 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	clean_fd(void)
{
	dup2(g_minishell.saved_stdin, 0);
	dup2(g_minishell.saved_stdout, 1);
}

void	src_pipe_read(void)
{
	dup2(g_minishell.fd[0], 0);
	close(g_minishell.fd[0]);
}

void	src_red_input(void)
{
	int		open_fd;
	char	*line;

	open_fd = open(g_minishell.phrase->next->name, O_RDONLY);
	while (get_next_line(open_fd, &line) > 0)
	{
		ft_putstr_fd(line, g_minishell.fd[1]);
		ft_putstr_fd("\n", g_minishell.fd[1]);
	}
	close(open_fd);
}

void	src_heredoc(void)
{
	char	*line;
	char	*limiter;
	int		ret;

	if (g_minishell.phrase->next)
		limiter = g_minishell.phrase->next->name;
	else
		limiter = NULL;
	ft_putstr_fd("> ", 1);
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			return ;
		}
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(line, g_minishell.fd[1]);
		ft_putstr_fd("\n", g_minishell.fd[1]);
	}
}

void	get_source(void)
{
	t_phrase	*phrase_og;

	phrase_og = g_minishell.phrase;
	if (g_minishell.phrase->prev && g_minishell.phrase->prev->op == PIPE)
		src_pipe_read();
	if (g_minishell.phrase->op == INPUT || g_minishell.phrase->op == READ)
	{
		if (pipe(g_minishell.fd) != 0)
			print_error("pipe failed in src_heredoc");
		while (g_minishell.phrase->op == INPUT || g_minishell.phrase->op == READ)
		{
			if (g_minishell.phrase->op == INPUT)
				src_red_input();
			if (g_minishell.phrase->op == READ)
				src_heredoc();
			g_minishell.phrase = g_minishell.phrase->next;
		}
		dup2(g_minishell.fd[0], 0);
		close(g_minishell.fd[0]);
		close(g_minishell.fd[1]);
	}
	g_minishell.phrase = phrase_og;
}

void	dest_pipe_write(void)
{
	if (pipe(g_minishell.fd) == -1)
		print_error("Pipe error");
	dup2(g_minishell.fd[1], 1);
	close(g_minishell.fd[1]);
}

void	dest_red_output(void)
{
	int	open_fd;
	t_phrase	*phrase_og;

	phrase_og = g_minishell.phrase;
	
	/* loop for consecutive output redirections
	** cat test1 > test > testing
	** will put output of cat test1 inside of newly created test, and testing
	*/
	while (g_minishell.phrase->op == OUTPUT || g_minishell.phrase->op == APPEND)
	{
		if (g_minishell.phrase->op == OUTPUT)
			open_fd = open(g_minishell.phrase->next->name, O_RDWR | O_CREAT, 0644);
		if (g_minishell.phrase->op == APPEND)
			open_fd = open(g_minishell.phrase->next->name, O_RDWR | O_APPEND | O_CREAT, 0644);
		g_minishell.saved_stdout = dup(1);
		dup2(open_fd, 1);
		close(open_fd);
		execution_control(phrase_og);
		clean_fd();
		g_minishell.phrase = g_minishell.phrase->next;
	}
}

void	get_dest(void)
{
	if (g_minishell.phrase->op == PIPE)
		dest_pipe_write();
	if (g_minishell.phrase->op == OUTPUT || g_minishell.phrase->op == APPEND)
		dest_red_output();
}

void	operation_control(void)
{
	get_source();
	get_dest();
	execution_control(g_minishell.phrase);
	clean_fd();
	while (g_minishell.phrase->op == INPUT || g_minishell.phrase->op == READ)
		g_minishell.phrase = g_minishell.phrase->next;
}
