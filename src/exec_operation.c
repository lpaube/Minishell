/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:54:03 by laube             #+#    #+#             */
/*   Updated: 2021/09/03 18:38:47 by laube            ###   ########.fr       */
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
	if (!phrase->next)
		close(phrase->fd[0]);
}

void	pipe_read(t_phrase *phrase)
{
	int	saved_stdin;

	saved_stdin = dup(0);
	dup2(phrase->prev->fd[0], 0);
	if (!phrase->next)
		execution_control(phrase);
	if (phrase->op == PIPE)
		pipe_write(phrase);
	dup2(saved_stdin, 0);
	close(phrase->prev->fd[0]);
	close(saved_stdin);
}

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
	if (phrase->prev)
	{
		if (phrase->prev->op == PIPE)
		{
			//printf("PREV: curr_name: %s\n", phrase->name);
			//printf("OP: %d\n", phrase->op);
			pipe_read(phrase);
		}
	}
	else if (phrase->next)
	{
		if (phrase->op == PIPE)
		{
			// printf("NEXT: curr_name: %s\n", phrase->name);
			//printf("OP: %d\n", phrase->op);
			pipe_write(phrase);
		}
		if (phrase->op == OUTPUT || phrase->op == APPEND)
		{
			redirect_write(phrase);
		}
	}
}
