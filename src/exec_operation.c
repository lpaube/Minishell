/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:54:03 by laube             #+#    #+#             */
/*   Updated: 2021/09/04 18:45:12 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


void	pipe_write(t_phrase *phrase)
{
	int	saved_stdout;

	phrase->fd = malloc(2 * sizeof(int));
	saved_stdout = dup(1);
	if (pipe(phrase->fd) == -1)
		print_error("pipe error");
	dup2(phrase->fd[1], 1);
	execution_control(phrase);
	dup2(saved_stdout, 1);
	close(phrase->fd[1]);
	close(saved_stdout);
}

void	src_pipe_read(t_phrase *phrase)
{
	phrase->saved_stdin = dup(0);
	dup2(phrase->prev->fd[0], 0);
}

void	src_red_input(t_phrase *phrase)
{
	int	open_fd;

	phrase->saved_stdin = dup(0);
	open_fd = open(phrase->next->name, O_RDONLY);
	dup2(open_fd, 0);
}

void	get_source(t_phrase *phrase)
{
	if (phrase->prev->op == PIPE)
		src_pipe_read(phrase);
	if (phrase->next->op == INPUT || phrase->next->op == READ)
		src_red_input(phrase);
}

void	get_dest(t_phrase *phrase)
{
	if (phrase->op == PIPE)
		dest_pipe_write(phrase);
	if (phrase->op == OUTPUT || phrase->op == APPEND)
		dest_red_output(phrase);
}

// void	pipe_read(t_phrase *phrase)
// {
// 	int	saved_stdin;

// 	saved_stdin = dup(0);
// 	dup2(phrase->prev->fd[0], 0);
// 	if (!phrase->next)
// 		execution_control(phrase);
// 	if (phrase->op == PIPE)
// 		pipe_write(phrase);
// 	dup2(saved_stdin, 0);
// 	close(phrase->prev->fd[0]);
// 	close(saved_stdin);
// }

void	redirect_write(t_phrase *phrase)
{
	int	open_fd;
	int	saved_stdout;

	if (phrase->op == APPEND)
	{
		open_fd = open(phrase->next->name, O_RDWR | O_APPEND | O_CREAT);
	}
	else if (phrase->op == OUTPUT)
	{
		open_fd = open(phrase->next->name, O_RDWR | O_CREAT);
	}
	else
		return ;
	//
	//NEED TO CHANGE ACCESS TO FILE IF NEWLY CREATED
	//
	saved_stdout = dup(1);
	dup2(open_fd, 1);
	execution_control(phrase);
	dup2(saved_stdout, 1);
	close(saved_stdout);
	close(open_fd);
}

void	operation_control(t_phrase *phrase)
{
	get_source(phrase);
	get_dest(phrase);
	execution_control(phrase);
	clean_fd(phrase);
}
