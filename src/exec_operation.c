/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:54:03 by laube             #+#    #+#             */
/*   Updated: 2021/09/07 16:05:36 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


void	src_pipe_read(t_phrase *phrase)
{
	phrase->saved_stdin = dup(0);
	dup2(phrase->prev->fd[0], 0);
	close(phrase->prev->fd[0]);
}

void	src_red_input(t_phrase *phrase)
{
	int	open_fd;

	phrase->saved_stdin = dup(0);
	open_fd = open(phrase->next->name, O_RDONLY);
	dup2(open_fd, 0);
	close(open_fd);
}

void	src_heredoc(t_phrase *phrase)
{
	char	*line;
	char	*limiter;
	int		ret;

	phrase->fd = malloc(2 * sizeof(int));
	phrase->saved_stdin = dup(0);
	if (pipe(phrase->fd) != 0)
		print_error("pipe failed in src_heredoc");
	if (phrase->next)
		limiter = phrase->next->name;
	else
		limiter = NULL;
	ft_putstr_fd("> ", 1);
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			dup2(phrase->fd[0], 0);
			close(phrase->fd[1]);
			return ;
		}
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(line, phrase->fd[1]);
		ft_putstr_fd("\n", phrase->fd[1]);
	}
}

void	get_source(t_phrase *phrase)
{

	if (phrase->prev && phrase->prev->op == PIPE)
		src_pipe_read(phrase);
	if (phrase->op == INPUT)
		src_red_input(phrase);
	if (phrase->op == READ)
		src_heredoc(phrase);
}

void	dest_pipe_write(t_phrase *phrase)
{
	phrase->saved_stdout = dup(1);
	phrase->fd = malloc(2 * sizeof(int));
	if (pipe(phrase->fd) == -1)
		print_error("Pipe error");
	dup2(phrase->fd[1], 1);
	close(phrase->fd[1]);
}

void	dest_red_output(t_phrase *phrase)
{
	int	open_fd;

	if (phrase->op == OUTPUT)
		open_fd = open(phrase->next->name, O_RDWR | O_CREAT);
	if (phrase->op == APPEND)
		open_fd = open(phrase->next->name, O_RDWR | O_APPEND | O_CREAT);
	phrase->saved_stdout = dup(1);
	dup2(open_fd, 1);
	close(open_fd);
}

void	get_dest(t_phrase *phrase)
{
	if (phrase->op == PIPE)
		dest_pipe_write(phrase);
	if (phrase->op == OUTPUT || phrase->op == APPEND)
		dest_red_output(phrase);
}

void	clean_fd(t_phrase *phrase)
{
	if ((phrase->prev && phrase->prev->op == PIPE) || phrase->op == INPUT || phrase->op == READ)
	{
		dup2(phrase->saved_stdin, 0);
		close(phrase->saved_stdin);
	}
	if (phrase->op == PIPE || phrase->op == OUTPUT || phrase->op == APPEND)
	{
		dup2(phrase->saved_stdout, 1);
		close(phrase->saved_stdout);
	}
}

void	operation_control(t_phrase *phrase)
{
	get_source(phrase);
	get_dest(phrase);
	execution_control(phrase);
	clean_fd(phrase);
}
