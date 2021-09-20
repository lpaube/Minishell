/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:18:50 by laube             #+#    #+#             */
/*   Updated: 2021/09/20 15:10:27 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "tokenizer.h"

static void	left_pipe(t_node *cmds)
{
	if (cmds->prev)
	{
		dup2(cmds->prev->fd[0], STDIN_FILENO);
		close(cmds->prev->fd[0]);
	}
}

static void	right_pipe(t_node *cmds)
{
	if (cmds->next)
		dup2(cmds->fd[1], STDOUT_FILENO);
}

void	op_control(t_node *cmds)
{
	pipe(cmds->fd);
	left_pipe(cmds);
	right_pipe(cmds);
	ft_lstiter(cmds->redirs, redirect);
	close(cmds->fd[1]);
	if (!cmds->next)
		close(cmds->fd[0]);
}
